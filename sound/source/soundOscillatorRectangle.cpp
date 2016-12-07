#include "soundOscillatorRectangle.h"

#include "mathConstants.h"

#include <cassert>

namespace
{
    double getPeriodPartsFromDuty(double duty);
    double getDutyFromPeriodParts(double period_parts);
}

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorRectangle::OscillatorRectangle()
  : mDuty(getPeriodPartsFromDuty(0.5))
{
}
///////////////////////////////////////////////////////////////////////////////
OscillatorRectangle::OscillatorRectangle(double frequency, double amplitude, double phase, double duty)
  : Oscillator(frequency, amplitude, phase)
  , mDuty(getPeriodPartsFromDuty(duty))
{
    assert(mDuty > 0.0);
    assert(mDuty < 100.0);
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorRectangle::getNextValue(double delta_time)
{
    double result = (getAccumulatedPhase() <= mDuty) ? getAmplitude() : -getAmplitude();

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
void OscillatorRectangle::setDuty(double duty)
{
    assert(duty > 0.0);
    assert(duty < 100.0);

    mDuty = getPeriodPartsFromDuty(duty);
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorRectangle::getDuty() const
{
    return getDutyFromPeriodParts(mDuty);
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
double getPeriodPartsFromDuty(double duty)
{
    return (duty * 2 * math::PI);
}
///////////////////////////////////////////////////////////////////////////////
double getDutyFromPeriodParts(double period_parts)
{
    return (period_parts / (2 * math::PI));
}
///////////////////////////////////////////////////////////////////////////////
}

