#pragma once

#include <cstddef>
#include <deque>


enum class Side
{
    Front,
    Back,
};


class BoundedList
{
    public:
        void set_capacity(long capacity);
        std::size_t size() const;
        const std::deque<char>& items() const;
        bool insert(Side side, char character);
        bool remove(Side side);

    private:
        long _capacity = -1; // (N >= 0) - length; (-1) - Unbounded;
        std::deque<char> _items;
};

