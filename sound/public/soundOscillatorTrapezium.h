/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_TRAPEZIUM_H__DDK
#define SOUND_OSCILLATOR_TRAPEZIUM_H__DDK

#include "soundOscillator.h"

namespace sound
{
    class OscillatorTrapezium
      : public Oscillator
    {
        public:
            OscillatorTrapezium();
            OscillatorTrapezium(double frequency, double amplitude, double phase, double raise, double fall);

            virtual double getNextValue(double delta_time);

        private:
            double mRaise;
            double mFall;
    };
}

#endif /* SOUND_OSCILLATOR_TRAPEZIUM_H__DDK */

