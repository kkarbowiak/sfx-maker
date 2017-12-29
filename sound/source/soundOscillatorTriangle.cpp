/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundOscillatorTriangle.h"

#include "mathConstants.h"

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorTriangle::OscillatorTriangle()
{
}
///////////////////////////////////////////////////////////////////////////////
OscillatorTriangle::OscillatorTriangle(double frequency, double amplitude, double phase)
  : Oscillator(frequency, amplitude, phase)
{
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorTriangle::getNextValue(double delta_time)
{
    double result = 0.0;

    if (getAccumulatedPhase() < math::PI / 2.0)
    {
        result = 2.0 / math::PI * getAmplitude() * getAccumulatedPhase();
    }
    else if (getAccumulatedPhase() < math::PI * 3.0 / 2.0)
    {
        result = getAmplitude() - 2.0 / math::PI * getAmplitude() * (getAccumulatedPhase() - math::PI / 2.0);
    }
    else
    {
        result = -getAmplitude() + 2.0 / math::PI * getAmplitude() * (getAccumulatedPhase() - math::PI * 3.0 / 2.0);
    }

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

