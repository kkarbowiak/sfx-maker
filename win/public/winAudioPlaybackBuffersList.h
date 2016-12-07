#ifndef WIN_AUDIO_PLAYBACK_BUFFERS_LIST_H__DDK
#define WIN_AUDIO_PLAYBACK_BUFFERS_LIST_H__DDK

#include "winEvent.h"
#include "winCriticalSection.h"

#include "FreeUsedList.h"

#include "windows.h"

namespace win
{
    class AudioPlaybackBuffersList
    {
        private:
            typedef FreeUsedList<WAVEHDR> container_type;

        public:
            typedef container_type::size_type     size_type;
            typedef container_type::free_iterator free_iterator;
            typedef container_type::used_iterator used_iterator;

        public:
            AudioPlaybackBuffersList(size_type num_buffers, size_type buffer_size_bytes);
            ~AudioPlaybackBuffersList();

            free_iterator getFreeBuffer();
            used_iterator getUsedBuffer();

            void appendToUsed(free_iterator fit);
            void appendToFree(used_iterator uit);

            bool free_empty();
            bool used_empty();

        private:
            container_type  mBuffersList;
            Event           mFreeNodeAvailableEvent;
            CriticalSection mCriticalSection;
    };
}

#endif /* WIN_AUDIO_PLAYBACK_BUFFERS_LIST_H__DDK */

