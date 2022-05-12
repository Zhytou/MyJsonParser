#include "AtomJson.hpp"
#include "Object.hpp"

namespace AtomJson
{
    Object::Pair::~Pair()
    {
        if (val)
            delete val;
    }

    Object::Object(size_t len)
    {
        size = 0;
        if (len < 10)
            capacity = 10;
        else
            capacity = len;
        p = new Pair[capacity];
    }

    Object::~Object()
    {
        if (p)
            delete[] p;
        size = 0;
        capacity = 0;
    }
} // namespace AtomJson
