/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "winScopedCriticalSectionEnter.h"
#include "winCriticalSection.h"

namespace win
{
///////////////////////////////////////////////////////////////////////////////
ScopedCriticalSectionEnter::ScopedCriticalSectionEnter(CriticalSection & cs)
  : mCriticalSection(cs)
{
    mCriticalSection.enter();
}
///////////////////////////////////////////////////////////////////////////////
ScopedCriticalSectionEnter::~ScopedCriticalSectionEnter()
{
    mCriticalSection.leave();
}
///////////////////////////////////////////////////////////////////////////////
}

