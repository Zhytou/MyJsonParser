#ifndef ATOMJSON_ARRAY_HPP
#define ATOMJSON_ARRAY_HPP

#include "AtomJson.hpp"

namespace AtomJson
{
    struct Value;

    class Array
    {
    public:
        /**
         * @brief Construct a new Array object
         *
         * @param len
         */
        Array(size_t len = 10);

        /**
         * @brief Destroy the Array object
         *
         */
        ~Array();

        /**
         * @brief
         *
         * @return true
         * @return false
         */
        bool empty() { return size == 0; }

        /**
         * @brief Get the length of the Array object
         *
         * @return size_t
         */
        size_t length() { return size; }

        /**
         * @brief
         *
         * @param idx
         * @return Value&
         */
        Value &operator[](size_t idx);

        /**
         * @brief
         *
         * @param val
         * @return Array&
         */
        Array &append(const Value &val);

    private:
        size_t size, capacity;
        Value *p;
    };

    Array::Array(size_t len)
    {
        size = 0;
        if (len < 10)
            capacity = 10;
        else
            capacity = len;
        p = new Value[capacity];
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
};
#endif