#pragma once
#include <vector>
#include <iostream>


template <typename T, typename Iterator>
class CyclicIterator : public std::iterator <std::random_access_iterator_tag, T, ptrdiff_t>
{
    Iterator   cursor;
    Iterator   begin;
    Iterator   end;

public:

    CyclicIterator (const Iterator& i, const Iterator& j) : cursor(i), begin(i), end(j) {}

    bool operator == (const CyclicIterator& x) const
    {
        return cursor == x.cursor;
    }

    bool operator != (const CyclicIterator& x) const
    {
        return ! (*this == x);
    }

    T& operator*() const
    {
        return *cursor;
    }

    CyclicIterator& operator++()
    {
        ++cursor;
        if (cursor == end)
            cursor = begin;
        return *this;
    }

    CyclicIterator& operator--()
    {
        if (cursor == begin)
            cursor = end;
        --cursor;
        return *this;
    }
};
