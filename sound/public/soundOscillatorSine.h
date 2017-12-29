/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_SINE_H__DDK
#define SOUND_OSCILLATOR_SINE_H__DDK

#include "soundOscillator.h"

namespace sound
{
    class OscillatorSine
      : public Oscillator
    {
        public:
            OscillatorSine();
            OscillatorSine(double frequency, double amplitude, double phase);

            virtual double getNextValue(double delta_time);
    };
}

#endif /* SOUND_OSCILLATOR_SINE_H__DDK */

