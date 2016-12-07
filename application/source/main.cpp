#include "applicationSFXMaker.h"
#include "applicationApplicationConfiguration.h"

#include "audioConfiguration.h"

#include <memory>
#include <string>

#include <cstddef> // NULL
#include <cstdio> // std::sscanf(), std::printf()

namespace
{
    void getConfigurationFromCommandLine(application::AppConfiguration & app_configuration, audio::Configuration & audio_configuration, int argc, char * argv[]);
    void displayHelp();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
    application::AppConfiguration app_configuration;
    app_configuration.display_help = false;

    audio::Configuration audio_configuration;
    audio_configuration.sample_rate                     = 44100;
    audio_configuration.sample_resolution               =    16;
    audio_configuration.channels_number                 =     2;
    audio_configuration.oscillator_type                 = audio::OT_SAWTOOTH;
    audio_configuration.main_oscillator_base_frequency  =   220.0;
    audio_configuration.main_oscillator_max_frequency   =  2200.0;
    audio_configuration.main_oscillator_min_frequency   =    55.0;
    audio_configuration.main_oscillator_delta_frequency =   440.0;
    audio_configuration.adsr_attack_time                =     0.2;
    audio_configuration.adsr_decay_time                 =     0.1;
    audio_configuration.adsr_sustain_time               =     1.0;
    audio_configuration.adsr_sustain_level              =     0.7;
    audio_configuration.adsr_release_time               =     1.5;
    audio_configuration.tremolo_frequency               =    15.0;
    audio_configuration.tremolo_depth                   =     0.3;
    audio_configuration.vibrato_frequency               =     7.0;
    audio_configuration.vibrato_depth                   =     0.1;
    audio_configuration.echo_delay                      =     0.0;
    audio_configuration.echo_gain                       =     0.0;
    audio_configuration.rect_base_duty                  =     0.5;
    audio_configuration.rect_delta_duty                 =     0.0;
    audio_configuration.lp_filter_cutoff                =     0.4;
    audio_configuration.lp_filter_cutoff_delta          =     0.0;
    audio_configuration.lp_filter_resonance             =     0.0;
    audio_configuration.hp_filter_cutoff                =     0.1;
    audio_configuration.hp_filter_cutoff_delta          =     0.0;
    audio_configuration.hp_filter_resonance             =     0.0;

    getConfigurationFromCommandLine(app_configuration, audio_configuration, argc, argv);

    int result = 0;

    if (!app_configuration.display_help)
    {
        std::auto_ptr<application::SFXMaker> sfx_maker_app_aptr(new application::SFXMaker);

        result = sfx_maker_app_aptr->execute(app_configuration, audio_configuration);
    }
    else
    {
        displayHelp();
    }

    return result;
}
///////////////////////////////////////////////////////////////////////////////

namespace
{
///////////////////////////////////////////////////////////////////////////////
void getConfigurationFromCommandLine(application::AppConfiguration & app_configuration, audio::Configuration & audio_configuration, int argc, char * argv[])
{
    std::string help("help");                // display usage
    std::string file("file=");               // file name
    std::string srate("srate=");             // sample rate
    std::string sres("sres=");               // sample resolution
    std::string chans("chans=");             // channels number
    std::string osc_type("osc_type=");       // oscillator type
    std::string base_freq("base_freq=");     // base frequency
    std::string max_freq("max_freq=");       // maximum frequency
    std::string min_freq("min_freq=");       // minimum frequency
    std::string delta_freq("delta_freq=");   // delta frequency
    std::string adsr_attack("adsr_attack="); // attack time
    std::string adsr_decay("adsr_decay=");   // decay time
    std::string adsr_sustt("adsr_sustt=");   // sustain time
    std::string adsr_sustl("adsr_sustl=");   // sustain level
    std::string adsr_rel("adsr_rel=");       // release time
    std::string trem_freq("trem_freq=");     // tremolo frequency
    std::string trem_depth("trem_depth=");   // tremolo depth
    std::string vib_freq("vib_freq=");       // vibrato frequency
    std::string vib_depth("vib_depth=");     // vibrato depth
    std::string echo_delay("echo_delay=");   // echo delay
    std::string echo_gain("echo_gain=");     // echo gain
    std::string base_duty("base_duty=");     // base duty factor for rectangular generator
    std::string delta_duty("delta_duty=");   // delta dury for rectangular generator
    std::string lp_cutoff("lp_cutoff=");     // low-pass filter cut off frequency
    std::string lp_delta("lp_delta=");       // low-pass cut off delta
    std::string lp_reson("lp_reson=");       // low-pass filter resonance
    std::string hp_cutoff("hp_cutoff=");     // high-pass filter cut off frequency
    std::string hp_delta("hp_delta=");       // high-pass cut off delta
    std::string hp_reson("hp_reson=");       // high-pass filter resonance

    for (int i = 1; i < argc; ++i)
    {
        std::string current_param(argv[i]);
        std::string::size_type pos;

        if ((pos = current_param.find(help)) != std::string::npos)
        {
            app_configuration.display_help = true;
        }
        else if ((pos = current_param.find(file)) != std::string::npos)
        {
            pos += file.length();
            app_configuration.file_name = current_param.substr(pos);
        }
        else if ((pos = current_param.find(srate)) != std::string::npos)
        {
            pos += srate.length();
            std::sscanf(current_param.substr(pos).c_str(), "%u", &audio_configuration.sample_rate);
        }
        else if ((pos = current_param.find(sres)) != std::string::npos)
        {
            pos += sres.length();
            std::sscanf(current_param.substr(pos).c_str(), "%u", &audio_configuration.sample_resolution);
        }
        else if ((pos = current_param.find(chans)) != std::string::npos)
        {
            pos += chans.length();
            std::sscanf(current_param.substr(pos).c_str(), "%u", &audio_configuration.channels_number);
        }
        else if ((pos = current_param.find(osc_type)) != std::string::npos)
        {
            pos += osc_type.length();
            std::sscanf(current_param.substr(pos).c_str(), "%i", &audio_configuration.oscillator_type);
        }
        else if ((pos = current_param.find(base_freq)) != std::string::npos)
        {
            pos += base_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.main_oscillator_base_frequency);
        }
        else if ((pos = current_param.find(max_freq)) != std::string::npos)
        {
            pos += max_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.main_oscillator_max_frequency);
        }
        else if ((pos = current_param.find(min_freq)) != std::string::npos)
        {
            pos += min_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.main_oscillator_min_frequency);
        }
        else if ((pos = current_param.find(delta_freq)) != std::string::npos)
        {
            pos += delta_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.main_oscillator_delta_frequency);
        }
        else if ((pos = current_param.find(adsr_attack)) != std::string::npos)
        {
            pos += adsr_attack.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.adsr_attack_time);
        }
        else if ((pos = current_param.find(adsr_decay)) != std::string::npos)
        {
            pos += adsr_decay.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.adsr_decay_time);
        }
        else if ((pos = current_param.find(adsr_sustt)) != std::string::npos)
        {
            pos += adsr_sustt.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.adsr_sustain_time);
        }
        else if ((pos = current_param.find(adsr_sustl)) != std::string::npos)
        {
            pos += adsr_sustl.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.adsr_sustain_level);
        }
        else if ((pos = current_param.find(adsr_rel)) != std::string::npos)
        {
            pos += adsr_rel.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.adsr_release_time);
        }
        else if ((pos = current_param.find(trem_freq)) != std::string::npos)
        {
            pos += trem_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.tremolo_frequency);
        }
        else if ((pos = current_param.find(trem_depth)) != std::string::npos)
        {
            pos += trem_depth.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.tremolo_depth);
        }
        else if ((pos = current_param.find(vib_freq)) != std::string::npos)
        {
            pos += vib_freq.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.vibrato_frequency);
        }
        else if ((pos = current_param.find(vib_depth)) != std::string::npos)
        {
            pos += vib_depth.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.vibrato_depth);
        }
        else if ((pos = current_param.find(echo_delay)) != std::string::npos)
        {
            pos += echo_delay.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.echo_delay);
        }
        else if ((pos = current_param.find(echo_gain)) != std::string::npos)
        {
            pos += echo_gain.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.echo_gain);
        }
        else if ((pos = current_param.find(base_duty)) != std::string::npos)
        {
            pos += base_duty.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.rect_base_duty);
        }
        else if ((pos = current_param.find(delta_duty)) != std::string::npos)
        {
            pos += delta_duty.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.rect_delta_duty);
        }
        else if ((pos = current_param.find(lp_cutoff)) != std::string::npos)
        {
            pos += lp_cutoff.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.lp_filter_cutoff);
        }
        else if ((pos = current_param.find(lp_delta)) != std::string::npos)
        {
            pos += lp_delta.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.lp_filter_cutoff_delta);
        }
        else if ((pos = current_param.find(lp_reson)) != std::string::npos)
        {
            pos += lp_reson.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.lp_filter_resonance);
        }
        else if ((pos = current_param.find(hp_cutoff)) != std::string::npos)
        {
            pos += hp_cutoff.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.hp_filter_cutoff);
        }
        else if ((pos = current_param.find(hp_delta)) != std::string::npos)
        {
            pos += hp_delta.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.hp_filter_cutoff_delta);
        }
        else if ((pos = current_param.find(hp_reson)) != std::string::npos)
        {
            pos += hp_reson.length();
            std::sscanf(current_param.substr(pos).c_str(), "%lf", &audio_configuration.hp_filter_resonance);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
void displayHelp()
{
    std::printf("available settings:\n"
                "help           : displays usage\n"
                "file           : sets output file name\n"
                "srate          : sample rate\n"
                "sres           : sample resolution\n"
                "chans          : channels number\n"
                "osc_type       : oscillator type\n"
                "base_freq      : base frequency\n"
                "max_freq       : maximum frequency\n"
                "min_freq       : minimum frequency\n"
                "delta_freq     : delta frequency\n"
                "adsr_attack    : attack time\n"
                "adsr_decay     : decay time\n"
                "adsr_sustt     : sustain time\n"
                "adsr_sustl     : sustain level\n"
                "adsr_rel       : release time\n"
                "trem_freq      : tremolo frequency\n"
                "trem_depth     : tremolo depth\n"
                "vib_freq       : vibrato frequency\n"
                "vib_depth      : vibrato depth\n"
                "echo_delay     : echo delay\n"
                "echo_gain      : echo gain\n"
                "base_duty      : base duty factor\n"
                "delta_duty     : delta duty\n"
                "lp_cutoff      : low-pass filter cut off\n"
                "lp_delta       : low-pass cut off delta\n"
                "lp_reson       : low-pass filter resonance\n"
                "hp_cutoff      : high-pass filter cut off\n"
                "hp_delta       : high-pass cut off delta\n"
                "hp_reson       : high-pass filter resonance\n");
}
///////////////////////////////////////////////////////////////////////////////
}
