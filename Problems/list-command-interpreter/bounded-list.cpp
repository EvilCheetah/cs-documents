#include "bounded-list.h"
#include <cstddef>


void BoundedList::set_capacity(long capacity)
{
    this->_capacity = capacity;
}


std::size_t BoundedList::size() const
{
    return this->_items.size();
}


const std::deque<char>& BoundedList::items() const
{
    return this->_items;
}


bool BoundedList::insert(Side side, char character)
{
    if (
        this->_capacity >= 0 &&
        static_cast<long>(this->items().size()) >= this->_capacity
    )
    {
        return false;
    }

    switch (side)
    {
        case Side::Front:
            this->_items.push_front(character);
            return true;

        case Side::Back:
            this->_items.push_back(character);
            return true;
    }

    // Exhaustive Option:
    // - Keep -> coverage is <100%
    // - Comment out -> -Wreturn-type warning
    // return false;
}


bool BoundedList::remove(Side side)
{
    if ( this->_items.empty() )
    {
        return false;
    }

    switch (side)
    {
        case Side::Front:
            this->_items.pop_front();
            return true;

        case Side::Back:
            this->_items.pop_back();
            return true;
    }

    // Exhaustive Option:
    // - Keep -> coverage is <100%
    // - Comment out -> -Wreturn-type warning
    // return false;
}
