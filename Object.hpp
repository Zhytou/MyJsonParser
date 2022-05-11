#ifndef ATOMJSON_OBJECT_HPP
#define ATOMJSON_OBJECT_HPP

#include "AtomJson.hpp"

namespace AtomJson
{
    struct Value;

    class Object
    {
    public:
        struct Pair
        {
            String key;
            Value *val;
            Pair() : key(), val(nullptr){};
            ~Pair()
            {
                if (val)
                    delete val;
            }
        };

        Object()
        {
            capacity = 1;
            // pairs = new Pair[capacity];
        }

        Object(size_t len);

        ~Object();

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
         * @param key
         * @return Value&
         */
        Value &operator[](String key);

    private:
        size_t size, capacity;
        Pair *p;
    };
};
#endif