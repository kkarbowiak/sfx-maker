#ifndef AUDIO_CONFIGURATION_H__DDK
#define AUDIO_CONFIGURATION_H__DDK

namespace audio
{
    enum eOscillatorType
    {
        OT_SINE,
        OT_SQUARE,
        OT_SAWTOOTH,
        OT_TRAPEZIUM,
        OT_TRIANGLE,
        OT_NOISE
    };

    struct Configuration
    {
        unsigned int    sample_rate;
        unsigned int    sample_resolution;
        unsigned int    channels_number;
        eOscillatorType oscillator_type;
        double          main_oscillator_base_frequency;
        double          main_oscillator_max_frequency;
        double          main_oscillator_min_frequency;
        double          main_oscillator_delta_frequency;
        double          adsr_attack_time;
        double          adsr_decay_time;
        double          adsr_sustain_time;
        double          adsr_sustain_level;
        double          adsr_release_time;
        double          tremolo_frequency;
        double          tremolo_depth;
        double          vibrato_frequency;
        double          vibrato_depth;
        double          echo_delay;
        double          echo_gain;
        double          lp_filter_cutoff;
        double          lp_filter_cutoff_delta;
        double          lp_filter_resonance;
        double          hp_filter_cutoff;
        double          hp_filter_cutoff_delta;
        double          hp_filter_resonance;
        double          rect_base_duty;
        double          rect_delta_duty;
    };
}

#endif /* AUDIO_CONFIGURATION_H__DDK */

