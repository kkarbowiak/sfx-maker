/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_TRIANGLE_H__DDK
#define SOUND_OSCILLATOR_TRIANGLE_H__DDK

#include "soundOscillator.h"

namespace sound
{
    class OscillatorTriangle
      : public Oscillator
    {
        public:
            OscillatorTriangle();
            OscillatorTriangle(double frequency, double amplitude, double phase);

            virtual double getNextValue(double delta_time);
    };
}

#endif /* SOUND_OSCILLATOR_TRIANGLE_H__DDK */

