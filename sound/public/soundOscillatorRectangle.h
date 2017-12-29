/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_RECTANGLE_H__DDK
#define SOUND_OSCILLATOR_RECTANGLE_H__DDK

#include "soundOscillator.h"

namespace sound
{
    class OscillatorRectangle
      : public Oscillator
    {
        public:
            OscillatorRectangle();
            OscillatorRectangle(double frequency, double amplitude, double phase, double duty);

            virtual double getNextValue(double delta_time);

            void   setDuty(double duty);
            double getDuty() const;

        private:
            double mDuty;
    };
}

#endif /* SOUND_OSCILLATOR_RECTANGLE_H__DDK */

