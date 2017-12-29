/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "winAudioPlaybackBuffersList.h"
#include "winScopedCriticalSectionEnter.h"

#include <cstddef> // NULL

namespace win
{
///////////////////////////////////////////////////////////////////////////////
AudioPlaybackBuffersList::AudioPlaybackBuffersList(size_type num_buffers, size_type buffer_size_bytes)
  : mBuffersList(num_buffers)
{
    for (free_iterator fit = mBuffersList.begin_free(); fit != mBuffersList.end_free(); ++fit)
    {
        fit->lpData          = new char[buffer_size_bytes];
        fit->dwBufferLength  = buffer_size_bytes;
        fit->dwBytesRecorded = 0;
        fit->dwUser          = 0;
        fit->dwFlags         = 0;
        fit->dwLoops         = 0;
        fit->lpNext          = NULL;
        fit->reserved        = 0;
    }

    if (!mBuffersList.free_empty())
    {
        mFreeNodeAvailableEvent.set();
    }
}
///////////////////////////////////////////////////////////////////////////////
AudioPlaybackBuffersList::~AudioPlaybackBuffersList()
{
    for (free_iterator fit = mBuffersList.begin_free(); fit != mBuffersList.end_free(); ++fit)
    {
        delete[] fit->lpData;
    }
}
///////////////////////////////////////////////////////////////////////////////
AudioPlaybackBuffersList::free_iterator AudioPlaybackBuffersList::getFreeBuffer()
{
    mFreeNodeAvailableEvent.wait();
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    return mBuffersList.getFreeNode();
}
///////////////////////////////////////////////////////////////////////////////
AudioPlaybackBuffersList::used_iterator AudioPlaybackBuffersList::getUsedBuffer()
{
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    return mBuffersList.getUsedNode();
}
///////////////////////////////////////////////////////////////////////////////
void AudioPlaybackBuffersList::appendToUsed(free_iterator fit)
{
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    mBuffersList.pushBackToUsed(fit);

    if (!mBuffersList.free_empty())
    {
        mFreeNodeAvailableEvent.set();
    }
}
///////////////////////////////////////////////////////////////////////////////
void AudioPlaybackBuffersList::appendToFree(used_iterator uit)
{
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    mBuffersList.pushBackToFree(uit);

    if (!mBuffersList.free_empty())
    {
        mFreeNodeAvailableEvent.set();
    }
}
///////////////////////////////////////////////////////////////////////////////
bool AudioPlaybackBuffersList::free_empty()
{
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    return mBuffersList.free_empty();
}
///////////////////////////////////////////////////////////////////////////////
bool AudioPlaybackBuffersList::used_empty()
{
    win::ScopedCriticalSectionEnter scse(mCriticalSection);

    return mBuffersList.used_empty();
}
///////////////////////////////////////////////////////////////////////////////
}

