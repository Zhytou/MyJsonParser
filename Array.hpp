#ifndef ATOMJSON_ARRAY_HPP
#define ATOMJSON_ARRAY_HPP

#include <iostream>

namespace AtomJson
{
    struct Value;

    class Array
    {
    public:
        /**
         * *Default constructor
         * @brief Construct a new Array object
         *
         * @param len
         */
        Array(size_t len = 10);

        /**
         * *Copy constructor
         * @brief Construct a new Array object  by another Array object
         *
         * @param other
         */
        Array(const Array &other);

        /**
         * *Move constructor
         * @brief Construct a new Array object by moving another Array object
         *
         * @param other
         */
        Array(Array &&other);

        /**
         * *Copy assignment operator
         * @brief Assign a new Array object by another Array object
         *
         * @param other
         * @return Array&
         */
        Array &operator=(const Array &other);

        /**
         * *Move assignment operator
         * @brief
         *
         * @param other
         * @return Array&
         */
        Array &operator=(Array &&other);

        /**
         * *Destructor
         * @brief Destroy the Array object
         *
         */
        ~Array();

        /**
         * @brief Check if the Array object is empty
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
         * *Overload the array index operator
         * @brief get the element in the idx position of the Array object
         *
         * @param idx
         * @return Value&
         */
        Value &operator[](size_t idx);

        /**
         * @brief
         *
         * @param other
         * @return bool
         */
        bool operator==(const Array &other);

        /**
         * @brief Add an element to the tail of Array object
         *
         * @param val
         * @return Array&
         */
        Array &append(const Value &val);

        /**
         * @brief Add an element to the tail of Array object
         *
         * @param val
         * @return Array&
         */
        Array &append(Value &&val);

        /**
         * @brief Pop the element at the tail of Array object
         *
         * @return Value
         */
        Value pop();

    private:
        size_t size, capacity;
        Value *p;
    };
};
#endif