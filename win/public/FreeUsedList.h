/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef FREE_USED_LIST_H__DDK
#define FREE_USED_LIST_H__DDK

#include <list>

template<typename T>
class FreeUsedList
{
    private:
        typedef std::list<T> list_type;

    public:
        typedef T value_type;
        typedef FreeUsedList<T> class_type;
        typedef typename list_type::size_type size_type;
        typedef typename list_type::iterator  free_iterator;
        typedef typename list_type::iterator  used_iterator;
        typedef typename list_type::const_iterator const_free_iterator;
        typedef typename list_type::const_iterator const_used_iterator;

    public:
        explicit FreeUsedList(size_type capacity);

        free_iterator getFreeNode();
        used_iterator getUsedNode();

        void pushFrontToUsed(free_iterator fit);
        void pushBackToUsed(free_iterator fit);

        void pushFrontToFree(used_iterator uit);
        void pushBackToFree(used_iterator uit);

        free_iterator begin_free();
        free_iterator end_free();

        const_free_iterator begin_free() const;
        const_free_iterator end_free() const;

        used_iterator begin_used();
        used_iterator end_used();

        const_used_iterator begin_used() const;
        const_used_iterator end_used() const;

        bool free_empty() const;
        bool used_empty() const;

        size_type free_size() const;
        size_type used_size() const;

    private:
        list_type mFreeNodes;
        list_type mUsedNodes;
};

///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline FreeUsedList<T>::FreeUsedList(size_type capacity)
  : mFreeNodes(capacity)
{
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::free_iterator FreeUsedList<T>::getFreeNode()
{
    return mFreeNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::used_iterator FreeUsedList<T>::getUsedNode()
{
    return mUsedNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void FreeUsedList<T>::pushFrontToUsed(free_iterator fit)
{
    mUsedNodes.splice(mUsedNodes.begin(), mFreeNodes, fit);
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void FreeUsedList<T>::pushBackToUsed(free_iterator fit)
{
    mUsedNodes.splice(mUsedNodes.end(), mFreeNodes, fit);
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void FreeUsedList<T>::pushFrontToFree(used_iterator uit)
{
    mFreeNodes.splice(mFreeNodes.begin(), mUsedNodes, uit);
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void FreeUsedList<T>::pushBackToFree(used_iterator uit)
{
    mFreeNodes.splice(mFreeNodes.end(), mUsedNodes, uit);
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::free_iterator FreeUsedList<T>::begin_free()
{
    return mFreeNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::free_iterator FreeUsedList<T>::end_free()
{
    return mFreeNodes.end();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::const_free_iterator FreeUsedList<T>::begin_free() const
{
    return mFreeNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::const_free_iterator FreeUsedList<T>::end_free() const
{
    return mFreeNodes.end();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::used_iterator FreeUsedList<T>::begin_used()
{
    return mUsedNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::used_iterator FreeUsedList<T>::end_used()
{
    return mUsedNodes.end();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::const_used_iterator FreeUsedList<T>::begin_used() const
{
    return mUsedNodes.begin();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::const_used_iterator FreeUsedList<T>::end_used() const
{
    return mUsedNodes.end();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool FreeUsedList<T>::free_empty() const
{
    return mFreeNodes.empty();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool FreeUsedList<T>::used_empty() const
{
    return mUsedNodes.empty();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::size_type FreeUsedList<T>::free_size() const
{
    return mFreeNodes.size();
}
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename FreeUsedList<T>::size_type FreeUsedList<T>::used_size() const
{
    return mUsedNodes.size();
}
///////////////////////////////////////////////////////////////////////////////

#endif /* FREE_USED_LIST_H__DDK */

