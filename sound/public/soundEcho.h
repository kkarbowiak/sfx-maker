/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_ECHO_H__DDK
#define SOUND_ECHO_H__DDK

#include "soundDelayLine.h"

#include <cstddef> // std::size_t

namespace sound
{
    class Echo
    {
        public:
            Echo(std::size_t delay_amount, double gain);

            double insertAndGet(double sample);

        private:
            DelayLine mDelayLine;
            double    mGain;
    };
}

#endif /* SOUND_ECHO_H__DDK */

