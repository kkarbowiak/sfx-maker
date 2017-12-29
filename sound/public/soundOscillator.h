/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_OSCILLATOR_H__DDK
#define SOUND_OSCILLATOR_H__DDK

namespace sound
{
    class Oscillator
    {
        public:
            virtual double getNextValue(double delta_time) = 0;

            void setFrequency(double frequency);
            void setAmplitude(double amplitude);
            void setPhase(double phase);

            double getFrequency() const;
            double getAmplitude() const;
            double getPhase() const;

            void resetState();

            virtual ~Oscillator() {}

        protected:
            Oscillator();
            Oscillator(double frequency, double amplitude, double phase);

            double getAccumulatedPhase() const;

            void increaseAccumulatedPhase(double delta_time);

        private:
            double mFrequency;
            double mAmplitude;
            double mPhase;
            double mAccumulatedPhase;
    };
}

#endif /* SOUND_OSCILLATOR_H__DDK */

