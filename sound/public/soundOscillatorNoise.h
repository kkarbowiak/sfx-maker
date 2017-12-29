/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_NOISE_H__DDK
#define SOUND_OSCILLATOR_NOISE_H__DDK

#include "soundOscillator.h"

#include <cstddef> // std::size_t

namespace sound
{
    class OscillatorNoise
      : public Oscillator
    {
        public:
            enum eNoiseType
            {
                NT_WHITE
            };

        public:
            OscillatorNoise();
            OscillatorNoise(eNoiseType noise_type, double frequency, double amplitude, double phase);
            ~OscillatorNoise();

            virtual double getNextValue(double delta_time);

        private:
            eNoiseType        mNoiseType;
            double *          mNoiseBuffer;
            const std::size_t mNoiseBufferLength;
    };
}

#endif /* SOUND_OSCILLATOR_NOISE_H__DDK */

