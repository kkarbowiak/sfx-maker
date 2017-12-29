/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef SOUND_FILTER_HIGH_PASS_H__DDK
#define SOUND_FILTER_HIGH_PASS_H__DDK

namespace sound
{
    class HighPassFilter
    {
        public:
            HighPassFilter();
            HighPassFilter(double cutoff, double resonance);

            double getFilteredSample(double input);

            double getCutoff() const;
            double getResonance() const;

            void setCutoff(double cutoff);
            void setResonance(double resonance);

        private:
            double mCutoff;
            double mResonance;
            double mCoeffA1;
            double mCoeffA2;
            double mCoeffA3;
            double mCoeffB1;
            double mCoeffB2;
            double mInputN1;
            double mInputN2;
            double mOutputN1;
            double mOutputN2;
    };
}

#endif /* SOUND_FILTER_HIGH_PASS_H__DDK */
