/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef WIN_SCOPED_CRITICAL_SECTION_ENTER_H__DDK
#define WIN_SCOPED_CRITICAL_SECTION_ENTER_H__DDK

namespace win { class CriticalSection; }

namespace win
{
    class ScopedCriticalSectionEnter
    {
        public:
            explicit ScopedCriticalSectionEnter(CriticalSection & cs);
            ~ScopedCriticalSectionEnter();

        private:
            ScopedCriticalSectionEnter(ScopedCriticalSectionEnter const &); // disabled
            ScopedCriticalSectionEnter & operator=(ScopedCriticalSectionEnter const &); // disabled

        private:
            CriticalSection & mCriticalSection;
    };
}

#endif /* WIN_SCOPED_CRITICAL_SECTION_ENTER_H__DDK */

