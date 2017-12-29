/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundFilterLowPass.h"

#include "mathConstants.h"

#include <cmath> // std::tan(), std::sqrt()

namespace
{
    void computeCoefficients(double cutoff, double resonance, double & a1, double & a2, double & a3, double & b1, double & b2);
}

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
LowPassFilter::LowPassFilter()
  : mCutoff(0.5)
  , mResonance(0.0)
  , mInputN1(0.0)
  , mInputN2(0.0)
  , mOutputN1(0.0)
  , mOutputN2(0.0)
{
    computeCoefficients(mCutoff, mResonance, mCoeffA1, mCoeffA2, mCoeffA3, mCoeffB1, mCoeffB2);
}
///////////////////////////////////////////////////////////////////////////////
LowPassFilter::LowPassFilter(double cutoff, double resonance)
  : mCutoff(cutoff)
  , mResonance(resonance)
  , mInputN1(0.0)
  , mInputN2(0.0)
  , mOutputN1(0.0)
  , mOutputN2(0.0)
{
    computeCoefficients(mCutoff, mResonance, mCoeffA1, mCoeffA2, mCoeffA3, mCoeffB1, mCoeffB2);
}
///////////////////////////////////////////////////////////////////////////////
double LowPassFilter::getFilteredSample(double input)
{
    // out(n) = a1 * in + a2 * in(n-1) + a3 * in(n-2) - b1 * out(n-1) - b2 * out(n-2)

    double output = mCoeffA1 * input + mCoeffA2 * mInputN1 + mCoeffA3 * mInputN2 - mCoeffB1 * mOutputN1 - mCoeffB2 * mOutputN2;

    mInputN2  = mInputN1;
    mInputN1  = input;
    mOutputN2 = mOutputN1;
    mOutputN1 = output;

    return output;
}
///////////////////////////////////////////////////////////////////////////////
double LowPassFilter::getCutoff() const
{
    return mCutoff;
}
///////////////////////////////////////////////////////////////////////////////
double LowPassFilter::getResonance() const
{
    return mResonance;
}
///////////////////////////////////////////////////////////////////////////////
void LowPassFilter::setCutoff(double cutoff)
{
    if (mCutoff != cutoff)
    {
        mCutoff = cutoff;

        computeCoefficients(mCutoff, mResonance, mCoeffA1, mCoeffA2, mCoeffA3, mCoeffB1, mCoeffB2);
    }
}
///////////////////////////////////////////////////////////////////////////////
void LowPassFilter::setResonance(double resonance)
{
    if (mResonance != resonance)
    {
        mResonance = resonance;

        computeCoefficients(mCutoff, mResonance, mCoeffA1, mCoeffA2, mCoeffA3, mCoeffB1, mCoeffB2);
    }
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
void computeCoefficients(double cutoff, double resonance, double & a1, double & a2, double & a3, double & b1, double & b2)
{
    static const double PI     = 3.1415926535897932384626433832795;
    static const double SQRT_2 = std::sqrt(2.0);
    const double c = 1.0 / std::tan(math::PI * cutoff);
    const double r = (0.1 - SQRT_2) * resonance + SQRT_2;

    a1 = 1.0 / (1.0 + r * c + c * c);
    a2 = 2.0 * a1;
    a3 = a1;
    b1 = 2.0 * (1.0 - c * c) * a1;
    b2 = (1.0 - r * c + c * c) * a1;
}
///////////////////////////////////////////////////////////////////////////////
}
