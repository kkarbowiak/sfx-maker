/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "winEvent.h"

#include <cstddef> // NULL

namespace win
{
///////////////////////////////////////////////////////////////////////////////
Event::Event()
{
    mEvent = CreateEvent(NULL, false, false, NULL);
    if (mEvent == NULL)
    {
        // handle the error
    }
}
///////////////////////////////////////////////////////////////////////////////
Event::~Event()
{
    if (CloseHandle(mEvent) == 0)
    {
        // handle the error
    }
}
///////////////////////////////////////////////////////////////////////////////
void Event::set()
{
    if (SetEvent(mEvent) == 0)
    {
        // handle the error
    }
}
///////////////////////////////////////////////////////////////////////////////
void Event::wait()
{
    DWORD result = WaitForSingleObject(mEvent, INFINITE);
    if (result != WAIT_OBJECT_0)
    {
        // handle the error
    }
}
///////////////////////////////////////////////////////////////////////////////
}

