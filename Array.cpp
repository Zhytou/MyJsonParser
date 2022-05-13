#include "AtomJson.hpp"
#include "Array.hpp"

namespace AtomJson
{
    Array::Array(size_t len)
    {
        size = 0;
        if (len < 10)
            capacity = 10;
        else
            capacity = len;
        p = new Value[capacity];
    }

    Array::Array(const Array &other)
    {
        size = other.size;
        capacity = other.capacity;
        if (capacity)
            p = new Value[capacity];

        for (size_t i = 0; i < size; i++)
            p[i] = other.p[i];
    }

    Array::Array(Array &&other)
    {
        size = other.size;
        capacity = other.capacity;
        p = other.p;

        other.size = 0;
        other.capacity = 0;
        other.p = nullptr;
    }

    Array &Array::operator=(const Array &other)
    {
        size = other.size;
        capacity = other.capacity;
        if (capacity)
            p = new Value[capacity];

        for (size_t i = 0; i < size; i++)
            p[i] = other.p[i];

        return *this;
    }

    Array &Array::operator=(Array &&other)
    {
        if (p && p != other.p)
            delete[] p;
        p = other.p;
        size = other.size;
        capacity = other.capacity;

        other.p = nullptr;
        other.size = 0;
        other.capacity = 0;

        return *this;
    }

    Array::~Array()
    {
        if (p)
            delete[] p;
        p = nullptr;
        size = 0;
        capacity = 0;
    }

    Value &Array::operator[](size_t idx)
    {
        assert(idx < size);
        return p[idx];
    }

    Array &Array::append(const Value &val)
    {
        if (size + 1 > capacity)
        {
            do
            {
                if (capacity == 0)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + 1 > capacity);

            if (p)
            {
                Value *np = new Value[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete[] p;
            }
            else
                p = new Value[capacity];
        }
        p[size] = val;
        size += 1;
        return *this;
    }

    Array &Array::append(Value &&val)
    {
        if (size + 1 > capacity)
        {
            do
            {
                if (capacity == 0)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + 1 > capacity);

            if (p)
            {
                Value *np = new Value[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete[] p;
            }
            else
                p = new Value[capacity];
        }
        p[size] = std::move(val);
        size += 1;
        return *this;
    }

    Value Array::pop()
    {
        assert(size >= 1);
        size -= 1;
        return Value(std::move(p[size]));
    }
} // namespace AtomJson
