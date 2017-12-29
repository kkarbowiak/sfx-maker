/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef WIN_PLAYBACK_ENGINE_H__DDK
#define WIN_PLAYBACK_ENGINE_H__DDK

#include "winAudioPlaybackBuffersList.h"

namespace audio { class AudioStack; }

namespace win
{
    class PlaybackEngine
    {
        public:
            PlaybackEngine();
            PlaybackEngine(unsigned int sample_rate, unsigned int sample_resolution, unsigned int channels_number);

            void setAudioStack(audio::AudioStack & audio_stack);

            void startPlayback();

        private:
            unsigned int             mSampleRate;
            unsigned int             mSampleResolution;
            unsigned int             mChannelsNumber;
            AudioPlaybackBuffersList mBuffersList;
            audio::AudioStack *      mAudioStackPtr;
    };
}

#endif /* WIN_PLAYBACK_ENGINE_H__DDK */

