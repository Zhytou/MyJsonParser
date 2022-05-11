#include "AtomJson.hpp"
#include "Object.hpp"

namespace AtomJson
{
    Object::Pair::~Pair()
    {
        if (val)
            delete val;
    }
} // namespace AtomJson
