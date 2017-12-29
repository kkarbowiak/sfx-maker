/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundDelayLine.h"

#include <algorithm> // std::fill()

namespace
{
    std::size_t wrapAround(std::size_t index, std::size_t max_index);
}

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
DelayLine::DelayLine(std::size_t delay_amount)
  : mBuffer(new double[delay_amount + 1])
  , mDelayAmount(delay_amount)
  , mWriteIndex(delay_amount)
  , mReadIndex(0)
{
    std::fill(mBuffer, mBuffer + mDelayAmount, 0.0);
}
///////////////////////////////////////////////////////////////////////////////
DelayLine::~DelayLine()
{
    delete[] mBuffer;
}
///////////////////////////////////////////////////////////////////////////////
double DelayLine::insertAndGet(double sample)
{
    mBuffer[mWriteIndex++] = sample;
    mWriteIndex = wrapAround(mWriteIndex, mDelayAmount);

    double output = mBuffer[mReadIndex++];
    mReadIndex = wrapAround(mReadIndex, mDelayAmount);

    return output;
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
std::size_t wrapAround(std::size_t index, std::size_t max_index)
{
    return (index > max_index ? 0 : index);
}
///////////////////////////////////////////////////////////////////////////////
}

