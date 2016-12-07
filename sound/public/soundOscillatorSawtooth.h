#ifndef SOUND_OSCILLATOR_SAWTOOTH_H__DDK
#define SOUND_OSCILLATOR_SAWTOOTH_H__DDK

#include "soundOscillator.h"

namespace sound
{
    class OscillatorSawtooth
      : public Oscillator
    {
        public:
            OscillatorSawtooth();
            OscillatorSawtooth(double frequency, double amplitude, double phase);

            virtual double getNextValue(double delta_time);
    };
}

#endif /* SOUND_OSCILLATOR_SAWTOOTH_H__DDK */

