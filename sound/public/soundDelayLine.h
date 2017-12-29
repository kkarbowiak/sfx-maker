/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_DELAY_LINE_H__DDK
#define SOUND_DELAY_LINE_H__DDK

#include <cstddef> // std::size_t

namespace sound
{
    class DelayLine
    {
        public:
            explicit DelayLine(std::size_t delay_amount);
            ~DelayLine();

            double insertAndGet(double sample);

        private:
            double *          mBuffer;
            const std::size_t mDelayAmount;
            std::size_t       mWriteIndex;
            std::size_t       mReadIndex;
    };
}

#endif /* SOUND_DELAY_LINE_H__DDK */

