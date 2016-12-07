#ifndef AUDIO_AUDIO_STACK_H__DDK
#define AUDIO_AUDIO_STACK_H__DDK

#include "audioConfiguration.h"

#include "soundOscillatorSine.h"
#include "soundOscillatorRectangle.h"
#include "soundOscillatorSawtooth.h"
#include "soundOscillatorTrapezium.h"
#include "soundOscillatorTriangle.h"
#include "soundOscillatorNoise.h"
#include "soundEcho.h"
#include "soundFilterLowPass.h"
#include "soundFilterHighPass.h"

namespace audio
{
    class AudioStack
    {
        public:
            AudioStack();
            explicit AudioStack(Configuration const & configuration);

            double getNextSample(double delta_time);

            void setConfiguration(Configuration const & configuration);

            void resetAudioState();

            bool isWaveformFinished();

        private:
            Configuration              mConfiguration;
            sound::OscillatorSine      mBaseSineOscillator;
            sound::OscillatorRectangle mBaseRectangleOscillator;
            sound::OscillatorSawtooth  mBaseSawtoothOscillator;
            sound::OscillatorTrapezium mBaseTrapeziumOscillator;
            sound::OscillatorTriangle  mBaseTriangleOscillator;
            sound::OscillatorNoise     mBaseNoiseOscillator;
            sound::OscillatorSine      mTremoloOscillator;
            sound::OscillatorSine      mVibratoOscillator;
            sound::Echo                mEcho;
            sound::LowPassFilter       mLPFilter;
            sound::HighPassFilter      mHPFilter;
            double                     mElapsedTime;
            bool                       mWaveformFinished;
    };
}

#endif /* AUDIO_AUDIO_STACK_H__DDK */

