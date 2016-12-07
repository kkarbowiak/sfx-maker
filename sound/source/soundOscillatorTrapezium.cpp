#include "soundOscillatorTrapezium.h"

#include "mathConstants.h"

#include <cassert>

namespace
{
    double getPeriodParts(double value);
}

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorTrapezium::OscillatorTrapezium()
  : mRaise(0.1)
  , mFall(0.1)
{
}
///////////////////////////////////////////////////////////////////////////////
OscillatorTrapezium::OscillatorTrapezium(double frequency, double amplitude, double phase, double raise, double fall)
  : Oscillator(frequency, amplitude, phase)
  , mRaise(getPeriodParts(raise) / 2.0)
  , mFall(getPeriodParts(fall) / 2.0)
{
    assert(mRaise > 0.0);
    assert(mRaise < math::PI);
    assert(mFall  > 0.0);
    assert(mFall  < math::PI);
    assert((mRaise + mFall) > 0.0);
    assert((mRaise + mFall) < math::PI);
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorTrapezium::getNextValue(double delta_time)
{
    double result = 0.0;

    if (getAccumulatedPhase() < math::PI)
    {
        if (getAccumulatedPhase() < mRaise)
        {
            result = getAmplitude() * getAccumulatedPhase() / mRaise;
        }
        else if (getAccumulatedPhase() > (math::PI - mFall))
        {
            result = getAmplitude() * (1.0 - (getAccumulatedPhase() - (math::PI - mFall)) / mFall);
        }
        else
        {
            result = getAmplitude();
        }
    }
    else
    {
        if (getAccumulatedPhase() - math::PI < mFall)
        {
            result = -getAmplitude() * (getAccumulatedPhase() - math::PI) / mFall;
        }
        else if (getAccumulatedPhase() - math::PI > math::PI - mRaise)
        {
            result = -getAmplitude() * (1.0 - (getAccumulatedPhase() - math::PI - (math::PI - mRaise)) / mRaise);
        }
        else
        {
            result = -getAmplitude();
        }
    }

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
double getPeriodParts(double value)
{
    return (value * 2.0 * math::PI);
}
///////////////////////////////////////////////////////////////////////////////
}

