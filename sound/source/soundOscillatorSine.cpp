/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundOscillatorSine.h"

#include "mathConstants.h"

#include <cmath> // std::sin()

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorSine::OscillatorSine()
{
}
///////////////////////////////////////////////////////////////////////////////
OscillatorSine::OscillatorSine(double frequency, double amplitude, double phase)
  : Oscillator(frequency, amplitude, phase)
{
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorSine::getNextValue(double delta_time)
{
    double result = getAmplitude() * std::sin(getAccumulatedPhase() + getPhase());

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

