/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "soundOscillatorNoise.h"

#include "mathConstants.h"

#include <cstdlib> // std::rand()

namespace
{
    double getRandomValue();
    void fillWithNoise(sound::OscillatorNoise::eNoiseType noise_type, double * buffer, std::size_t size);
}

namespace sound
{
///////////////////////////////////////////////////////////////////////////////
OscillatorNoise::OscillatorNoise()
  : mNoiseType(NT_WHITE)
  , mNoiseBuffer(new double[32])
  , mNoiseBufferLength(32)
{
    fillWithNoise(mNoiseType, mNoiseBuffer, mNoiseBufferLength);
}
///////////////////////////////////////////////////////////////////////////////
OscillatorNoise::OscillatorNoise(eNoiseType noise_type, double frequency, double amplitude, double phase)
  : Oscillator(frequency, amplitude, phase)
  , mNoiseType(noise_type)
  , mNoiseBuffer(new double[32])
  , mNoiseBufferLength(32)
{
    fillWithNoise(mNoiseType, mNoiseBuffer, mNoiseBufferLength);
}
///////////////////////////////////////////////////////////////////////////////
OscillatorNoise::~OscillatorNoise()
{
    delete[] mNoiseBuffer;
}
///////////////////////////////////////////////////////////////////////////////
double OscillatorNoise::getNextValue(double delta_time)
{
    double result = mNoiseBuffer[static_cast<std::size_t>(getAccumulatedPhase() / (2.0 * math::PI) * mNoiseBufferLength)];

    increaseAccumulatedPhase(delta_time);

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

namespace
{
///////////////////////////////////////////////////////////////////////////////
double getRandomValue()
{
    return (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
}
///////////////////////////////////////////////////////////////////////////////
void fillWithNoise(sound::OscillatorNoise::eNoiseType noise_type, double * buffer, std::size_t size)
{
    for (std::size_t index = 0; index < size; ++index)
    {
        switch (noise_type)
        {
             case sound::OscillatorNoise::NT_WHITE:
                 buffer[index] = -1.0 + 2.0 * getRandomValue();
                 break;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
}

