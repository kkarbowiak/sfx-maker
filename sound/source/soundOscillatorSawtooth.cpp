/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundOscillatorSawtooth.h"

#include "mathConstants.h"

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorSawtooth::OscillatorSawtooth()
{
}
///////////////////////////////////////////////////////////////////////////////
OscillatorSawtooth::OscillatorSawtooth(double frequency, double amplitude, double phase)
  : Oscillator(frequency, amplitude, phase)
{
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorSawtooth::getNextValue(double delta_time)
{
    double result = -getAmplitude() + (getAmplitude() / math::PI * getAccumulatedPhase());

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

