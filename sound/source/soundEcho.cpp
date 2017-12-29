/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundEcho.h"

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
Echo::Echo(std::size_t delay_amount, double gain)
  : mDelayLine(delay_amount)
  , mGain(gain)
{
}
///////////////////////////////////////////////////////////////////////////////
double Echo::insertAndGet(double sample)
{
    double delayed = mDelayLine.insertAndGet(sample);

    return (sample + mGain * delayed);
}
///////////////////////////////////////////////////////////////////////////////
}

