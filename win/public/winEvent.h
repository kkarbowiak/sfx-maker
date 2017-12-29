/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef WIN_EVENT_H__DDK
#define WIN_EVENT_H__DDK

#include "windows.h"

namespace win
{
    class Event
    {
        public:
            Event();
            ~Event();

            void set();
            void wait();

        private:
            Event(Event const &); // disabled
            Event & operator=(Event const &); // disabled

        private:
            HANDLE mEvent;
    };
}

#endif /* WIN_EVENT_H__DDK */

