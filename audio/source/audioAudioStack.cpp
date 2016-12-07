#include "audioAudioStack.h"

#include <cassert>

namespace
{
    double getClippedValue(double value, double min, double max);
}

namespace audio
{
///////////////////////////////////////////////////////////////////////////////
AudioStack::AudioStack()
  : mElapsedTime(0.0)
  , mEcho(0, 0.0)
  , mWaveformFinished(false)
{
}
///////////////////////////////////////////////////////////////////////////////
AudioStack::AudioStack(Configuration const & configuration)
  : mConfiguration(configuration)
  , mBaseSineOscillator(configuration.main_oscillator_base_frequency, 1.0, 0.0)
  , mBaseRectangleOscillator(configuration.main_oscillator_base_frequency, 1.0, 0.0, configuration.rect_base_duty)
  , mBaseSawtoothOscillator(configuration.main_oscillator_base_frequency, 1.0, 0.0)
  , mBaseTrapeziumOscillator(configuration.main_oscillator_base_frequency, 1.0, 0.0, 0.333, 0.333)
  , mBaseTriangleOscillator(configuration.main_oscillator_base_frequency, 1.0, 0.0)
  , mBaseNoiseOscillator(sound::OscillatorNoise::NT_WHITE, configuration.main_oscillator_base_frequency, 1.0, 0.0)
  , mTremoloOscillator(configuration.tremolo_frequency, 1.0, 0.0)
  , mVibratoOscillator(configuration.vibrato_frequency, 1.0, 0.0)
  , mEcho(static_cast<std::size_t>(configuration.echo_delay * configuration.sample_rate), configuration.echo_gain)
  , mLPFilter(configuration.lp_filter_cutoff, configuration.lp_filter_resonance)
  , mHPFilter(configuration.hp_filter_cutoff, configuration.hp_filter_resonance)
  , mElapsedTime(0.0)
  , mWaveformFinished(false)
{
}
///////////////////////////////////////////////////////////////////////////////
double AudioStack::getNextSample(double delta_time)
{
    double output_sample = 0.0;

    if (!mWaveformFinished)
    {
        // get new frequency
        double next_frequency = mConfiguration.main_oscillator_base_frequency + mElapsedTime * mConfiguration.main_oscillator_delta_frequency;

        // apply vibrato
        next_frequency *= (1.0 + mConfiguration.vibrato_depth * mVibratoOscillator.getNextValue(delta_time));
        if (next_frequency < mConfiguration.main_oscillator_min_frequency)
        {
            next_frequency = mConfiguration.main_oscillator_min_frequency;
            mWaveformFinished = true;
        }
        else if (next_frequency > mConfiguration.main_oscillator_max_frequency)
        {
            next_frequency = mConfiguration.main_oscillator_max_frequency;
            mWaveformFinished = true;
        }

        // get value from base oscillator
        switch (mConfiguration.oscillator_type)
        {
            case OT_SINE:
            {
                output_sample = mBaseSineOscillator.getNextValue(delta_time);
                mBaseSineOscillator.setFrequency(next_frequency);
                break;
            }

            case OT_SQUARE:
            {
                output_sample = mBaseRectangleOscillator.getNextValue(delta_time);
                mBaseRectangleOscillator.setFrequency(next_frequency);

                // apply duty delta
                double next_duty = mBaseRectangleOscillator.getDuty() + mConfiguration.rect_delta_duty * delta_time;
                next_duty = getClippedValue(next_duty, 0.001, 0.999);
                mBaseRectangleOscillator.setDuty(next_duty);
                break;
            }

            case OT_SAWTOOTH:
            {
                output_sample = mBaseSawtoothOscillator.getNextValue(delta_time);
                mBaseSawtoothOscillator.setFrequency(next_frequency);
                break;
            }

            case OT_TRAPEZIUM:
            {
                output_sample = mBaseTrapeziumOscillator.getNextValue(delta_time);
                mBaseTrapeziumOscillator.setFrequency(next_frequency);
                break;
            }

            case OT_TRIANGLE:
            {
                output_sample = mBaseTriangleOscillator.getNextValue(delta_time);
                mBaseTriangleOscillator.setFrequency(next_frequency);
                break;
            }

            case OT_NOISE:
            {
                output_sample = mBaseNoiseOscillator.getNextValue(delta_time);
                mBaseNoiseOscillator.setFrequency(next_frequency);
                break;
            }
        }

        // apply low-pass filter
        output_sample = mLPFilter.getFilteredSample(output_sample);
        double next_lp_cutoff = getClippedValue(mLPFilter.getCutoff() + mConfiguration.lp_filter_cutoff_delta * delta_time, 0.000001, 0.5);
        mLPFilter.setCutoff(next_lp_cutoff);
        
        // apply high-pass filter
        output_sample = mHPFilter.getFilteredSample(output_sample);
        double next_hp_cutoff = getClippedValue(mHPFilter.getCutoff() + mConfiguration.hp_filter_cutoff_delta * delta_time, 0.0, 0.5);
        mHPFilter.setCutoff(next_hp_cutoff);

        // apply tremolo
        output_sample *= 1.0 - mConfiguration.tremolo_depth + mConfiguration.tremolo_depth * mTremoloOscillator.getNextValue(delta_time);

        // apply echo
        output_sample = mEcho.insertAndGet(output_sample);

        // apply envelope
        double elapsed_time = mElapsedTime;
        if (elapsed_time < mConfiguration.adsr_attack_time)
        {
            output_sample *= mElapsedTime / mConfiguration.adsr_attack_time;
        }
        else
        {
            elapsed_time -= mConfiguration.adsr_attack_time;
            if (elapsed_time < mConfiguration.adsr_decay_time)
            {
                output_sample *= elapsed_time * (mConfiguration.adsr_sustain_level - 1.0) / mConfiguration.adsr_decay_time + 1.0;
            }
            else
            {
                elapsed_time -= mConfiguration.adsr_decay_time;
                if (elapsed_time < mConfiguration.adsr_sustain_time)
                {
                    output_sample *= mConfiguration.adsr_sustain_level;
                }
                else
                {
                    elapsed_time -= mConfiguration.adsr_sustain_time;
                    if (elapsed_time < mConfiguration.adsr_release_time)
                    {
                        output_sample *= mConfiguration.adsr_sustain_level * (1.0 - elapsed_time / mConfiguration.adsr_release_time);
                    }
                    else
                    {
                        mWaveformFinished = true;
                    }
                }
            }
        }

        // apply clipping
        output_sample = getClippedValue(output_sample, -1.0, 1.0);

        // increase elapsed time
        mElapsedTime += delta_time;
    }

    return output_sample;
}
///////////////////////////////////////////////////////////////////////////////
void AudioStack::setConfiguration(Configuration const & configuration)
{
    mConfiguration = configuration;

    mBaseSineOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mBaseRectangleOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mBaseSawtoothOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mBaseTrapeziumOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mBaseTriangleOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mBaseNoiseOscillator.setFrequency(configuration.main_oscillator_base_frequency);
    mTremoloOscillator.setFrequency(configuration.tremolo_frequency);
    mVibratoOscillator.setFrequency(configuration.vibrato_frequency);
    mLPFilter.setCutoff(configuration.lp_filter_cutoff);
    mLPFilter.setResonance(configuration.lp_filter_resonance);
    mHPFilter.setCutoff(configuration.hp_filter_cutoff);
    mHPFilter.setResonance(configuration.hp_filter_resonance);
}
///////////////////////////////////////////////////////////////////////////////
void AudioStack::resetAudioState()
{
    mElapsedTime = 0.0;

    mBaseSineOscillator.resetState();
    mBaseRectangleOscillator.resetState();
    mBaseSawtoothOscillator.resetState();
    mBaseTrapeziumOscillator.resetState();
    mBaseTriangleOscillator.resetState();
    mBaseNoiseOscillator.resetState();
    mTremoloOscillator.resetState();
    mVibratoOscillator.resetState();
}
///////////////////////////////////////////////////////////////////////////////
bool AudioStack::isWaveformFinished()
{
    return mWaveformFinished;
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
double getClippedValue(double value, double min, double max)
{
    assert(min <= max);

    return (value < min ? min : value > max ? max : value);
}
///////////////////////////////////////////////////////////////////////////////
}

