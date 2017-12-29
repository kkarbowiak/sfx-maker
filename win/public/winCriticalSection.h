/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef WIN_CRITICAL_SECTION_H__DDK
#define WIN_CRITICAL_SECTION_H__DDK

#include "windows.h"

namespace win
{
    class CriticalSection
    {
        public:
            CriticalSection();
            ~CriticalSection();

            void enter();
            bool try_enter();
            void leave();

        private:
            CriticalSection(CriticalSection const &); // disabled
            CriticalSection & operator=(CriticalSection const &); // disabled

        private:
            CRITICAL_SECTION mCriticalSection;
    };
}

#endif /* WIN_CRITICAL_SECTION_H__DDK */

