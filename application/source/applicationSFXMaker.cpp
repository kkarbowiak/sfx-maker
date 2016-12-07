#include "applicationSFXMaker.h"
#include "applicationApplicationConfiguration.h"

#include "winPlaybackEngine.h"

#include "audioConfiguration.h"
#include "audioAudioStack.h"

#include "wavStructures.h"

#include "fileExportToWAVFile.h"

#include <vector>

namespace application
{
///////////////////////////////////////////////////////////////////////////////
SFXMaker::SFXMaker()
{
}
///////////////////////////////////////////////////////////////////////////////
int SFXMaker::execute(AppConfiguration const & app_configuration, audio::Configuration const & audio_configuration)
{
    int result = 0;

    audio::AudioStack audio_stack(audio_configuration);

    if (app_configuration.file_name.empty())
    {
        win::PlaybackEngine playback_engine;

        playback_engine.setAudioStack(audio_stack);
        playback_engine.startPlayback();
    }
    else
    {
        const std::vector<double>::size_type estimated_samples_number = static_cast<std::vector<double>::size_type>
                                                                        (audio_configuration.sample_rate *
                                                                         (audio_configuration.adsr_attack_time  +
                                                                          audio_configuration.adsr_decay_time   +
                                                                          audio_configuration.adsr_sustain_time +
                                                                          audio_configuration.adsr_release_time));
        std::vector<double> samples;
        samples.reserve(estimated_samples_number);

        while (!audio_stack.isWaveformFinished())
        {
            samples.push_back(audio_stack.getNextSample(1.0 / audio_configuration.sample_rate));
        }

        wav::Format wav_format = {audio_configuration.sample_rate,
                                  audio_configuration.sample_resolution,
                                  audio_configuration.channels_number};

        bool file_result = file::exportToWAVFile(app_configuration.file_name, wav_format, samples);

        if (!file_result)
        {
            result = 1;
        }
    }
    
    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

