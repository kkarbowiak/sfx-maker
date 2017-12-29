/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "winPlaybackEngine.h"

#include "audioAudioStack.h"

#include "windows.h"

#include <vector>

#include <cstddef> // NULL
#include <cassert>

namespace
{
    const unsigned int DEFAULT_SAMPLE_RATE       = 44100;
    const unsigned int DEFAULT_CHANNELS_NUMBER   =     2;
    const unsigned int DEFAULT_SAMPLE_RESOLUTION =    16;
    const unsigned int FRAGMENTS_NUMBER          =    20;
    const unsigned int FRAGMENT_SIZE_SAMPLES     =   100;
    const unsigned int FRAGMENT_SIZE_BYTES       = FRAGMENT_SIZE_SAMPLES * DEFAULT_CHANNELS_NUMBER * DEFAULT_SAMPLE_RESOLUTION / 8;
}

namespace
{
    void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    unsigned char getLowByte(short sh);
    unsigned char getHighByte(short sh);

    void copyToBuffer(char * buffer, std::size_t buffer_size, double const * samples_ptr);
}

namespace win
{
///////////////////////////////////////////////////////////////////////////////
PlaybackEngine::PlaybackEngine()
  : mSampleRate(DEFAULT_SAMPLE_RATE)
  , mSampleResolution(DEFAULT_SAMPLE_RESOLUTION)
  , mChannelsNumber(DEFAULT_CHANNELS_NUMBER)
  , mBuffersList(FRAGMENTS_NUMBER, FRAGMENT_SIZE_BYTES)
  , mAudioStackPtr(NULL)
{
}
///////////////////////////////////////////////////////////////////////////////
PlaybackEngine::PlaybackEngine(unsigned int sample_rate, unsigned int sample_resolution, unsigned int channels_number)
  : mSampleRate(sample_rate)
  , mSampleResolution(sample_resolution)
  , mChannelsNumber(channels_number)
  , mBuffersList(FRAGMENTS_NUMBER, channels_number * sample_resolution / 8)
  , mAudioStackPtr(NULL)
{
}
///////////////////////////////////////////////////////////////////////////////
void PlaybackEngine::setAudioStack(audio::AudioStack & audio_stack)
{
    mAudioStackPtr = &audio_stack;
}
///////////////////////////////////////////////////////////////////////////////
void PlaybackEngine::startPlayback()
{
    assert(mAudioStackPtr != NULL);

    std::vector<double> sample_buffer(FRAGMENT_SIZE_SAMPLES);

    const double delta_time  = 1.0 / mSampleRate;
    const double output_gain = 10000.0;

    HWAVEOUT     device_handle;
    WAVEFORMATEX wfx;

    wfx.nSamplesPerSec  = mSampleRate;       // sample rate
    wfx.wBitsPerSample  = mSampleResolution; // sample size
    wfx.nChannels       = mChannelsNumber;   // channels
    wfx.cbSize          = 0;                 // size of extra info
    wfx.wFormatTag      = WAVE_FORMAT_PCM;
    wfx.nBlockAlign     = (wfx.wBitsPerSample * wfx.nChannels) / 8;
    wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

    MMRESULT result = waveOutOpen(&device_handle, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc, (DWORD_PTR)&mBuffersList, CALLBACK_FUNCTION);
    if(result == MMSYSERR_NOERROR)
    {
        while (!mAudioStackPtr->isWaveformFinished())
        {
            AudioPlaybackBuffersList::free_iterator fit = mBuffersList.getFreeBuffer();
            if ((fit->dwFlags & WHDR_PREPARED) != 0)
            {
                result = waveOutUnprepareHeader(device_handle, &(*fit), sizeof(*fit));
                if(result != MMSYSERR_NOERROR)
                {
                    // report waveOutUnprepareHeader() error

                    std::printf("waveOutUnprepareHeader() failed with code %u\n", result);
                }
            }

            for (std::vector<double>::iterator it = sample_buffer.begin(); it != sample_buffer.end(); ++it)
            {
                *it = output_gain * mAudioStackPtr->getNextSample(delta_time);
            }

            copyToBuffer(fit->lpData, fit->dwBufferLength, &sample_buffer.front());

            result = waveOutPrepareHeader(device_handle, &(*fit), sizeof(*fit));
            if (result != MMSYSERR_NOERROR)
            {
                // report waveOutPrepareHeader() error

                std::printf("waveOutPrepareHeader() failed with code %u\n", result);
            }

            result = waveOutWrite(device_handle, &(*fit), sizeof(*fit));
            if (result != MMSYSERR_NOERROR)
            {
                // report waveOutWrite() error

                std::printf("waveOutWrite() failed with code %u\n", result);
            }

            mBuffersList.appendToUsed(fit);
        }

        // wait for playback to finish
        while (!mBuffersList.used_empty())
        {
            Sleep(static_cast<DWORD>(static_cast<double>(1000 * FRAGMENT_SIZE_SAMPLES) / static_cast<double>(mSampleRate)));
        }

        // unprepare all remaining fragments
        while (!mBuffersList.free_empty())
        {
            AudioPlaybackBuffersList::free_iterator fit =  mBuffersList.getFreeBuffer();
            if ((fit->dwFlags & WHDR_PREPARED) != 0)
            {
                result = waveOutUnprepareHeader(device_handle, &(*fit), sizeof(*fit));
                if (result != MMSYSERR_NOERROR)
                {
                    // report waveOutUnprepareHeader() error

                    std::printf("waveOutUnprepareHeader() failed with code %u\n", result);
                }
            }

            mBuffersList.appendToUsed(fit);
        }

        result = waveOutClose(device_handle);
        if(result != MMSYSERR_NOERROR)
        {
            // report waveOutClose() error

            std::printf("waveOutClose() failed with code %u\n", result);
        }
    }
    else
    {
        // report waveOutOpen() error

        std::printf("waveOutOpen() failed with code %u\n", result);
    }
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    if (uMsg == WOM_DONE)
    {
        win::AudioPlaybackBuffersList * apbl_ptr = reinterpret_cast<win::AudioPlaybackBuffersList *>(dwInstance);

        apbl_ptr->appendToFree(apbl_ptr->getUsedBuffer());
    }
}
///////////////////////////////////////////////////////////////////////////////
unsigned char getLowByte(short sh)
{
    return (sh & 0xff);
}
///////////////////////////////////////////////////////////////////////////////
unsigned char getHighByte(short sh)
{
    return ((sh >> 8) & 0xff);
}
///////////////////////////////////////////////////////////////////////////////
void copyToBuffer(char * buffer, std::size_t buffer_size, double const * samples_ptr)
{
    for (std::size_t index = 0; index < buffer_size / (DEFAULT_CHANNELS_NUMBER * DEFAULT_SAMPLE_RESOLUTION / 8);)
    {
        short sample_val  = static_cast<short>(*samples_ptr);

        buffer[4 * index]     = getLowByte(sample_val);
        buffer[4 * index + 1] = getHighByte(sample_val);
        buffer[4 * index + 2] = getLowByte(sample_val);
        buffer[4 * index + 3] = getHighByte(sample_val);

        ++index;
        ++samples_ptr;
    }
}
///////////////////////////////////////////////////////////////////////////////
}

