#ifndef ATOMJSON_OBJECT_HPP
#define ATOMJSON_OBJECT_HPP

#include <iostream>
#include "Array.hpp"

namespace AtomJson
{
    class Value;

    struct DoubleyLinkedListNode;
    typedef DoubleyLinkedListNode Node;

    class Object
    {
    public:
        struct Item
        {
            String key;
            Value *val;

            /**
             * *Default constructor
             * @brief Construct a new Item object
             *
             */
            Item() : val(nullptr) {}

            /**
             * @brief Construct a new Item object
             *
             * @param k
             */
            Item(const String &k, Value *v = nullptr) : key(k), val(v) {}

            /**
             * *Copy constructor
             * @brief Construct a new Item object by copying another Item object
             *
             * @param other
             */
            Item(const Item &other);

            /**
             * *Move constructor
             * @brief Construct a new Item object by moving another Item object
             *
             * @param other
             */
            Item(Item &&other);

            /**
             * *Copy assignment operator
             * @brief Assign a new Item object by another Item object
             *
             * @param other
             * @return Item&
             */
            Item &operator=(const Item &other);

            /**
             * *Move assignment operator
             * @brief Assign a new Item object by moving another Item object
             *
             * @param other
             * @return Item&
             */
            Item &operator=(Item &&other);

            /**
             * *Destructor
             *  @brief Destroy the Item object
             *
             */
            ~Item();
        };

        /**
         * *Default constructor
         * @brief Construct a new Object object
         *
         * @param len
         */
        Object();

        /**
         * *Copy constructor
         * @brief Construct a new Object object
         *
         * @param other
         */
        Object(const Object &other);

        /**
         * *Move constructor
         * @brief Construct a new Object object by moving another Object object
         *
         * @param other
         */
        Object(Object &&other);

        /**
         * *Copy assignment operator
         * @brief
         *
         * @param other
         * @return Object&
         */
        Object &operator=(const Object &other);

        /**
         * *Move assignment operator
         * @brief
         *
         * @param other
         * @return Object&
         */
        Object &operator=(Object &&other);

        /**
         * *Destructor
         * @brief Destroy the Object object
         *
         */
        ~Object();

        /**
         * @brief Check if the Object is empty
         *
         * @return bool
         */
        bool empty() const { return size == 0; }

        /**
         * @brief Get the length of the Object object
         *
         * @return size_t
         */
        size_t length() const { return size; }

        /**
         * ! Be careful, calling this function automatically insert a new Item object whose key equals the param key no matter if the Item existed or not. (just like the map [] function in STL C++ library)
         * @brief
         *
         * @param key
         * @return Value&
         */
        Value &operator[](const String &key);

        /**
         * ! Be careful, the key must be already in the object
         * @brief
         *
         * @param key
         * @return const Value&
         */
        const Value &operator[](const String &key) const;

        /**
         * ! Be careful, this function checks if the structures and contents of the two objects are exactly the same.
         * @brief Check if the two Object objects are exactly the same
         *
         * @param other
         * @return bool
         */
        bool operator==(const Object &other) const;

        /**
         * @brief Check if the key exist in the Object
         *
         * @param key
         * @return bool
         */
        bool exist(const String &key) const;

        /**
         * @brief Get an Array of all the keys in the Object
         *
         * @return Array
         */
        Array keys() const;

        /**
         * @brief Get an Array of all the values in the Object
         *
         * @return Array
         */
        Array values() const;

    private:
        bool need_resize()
        {
            loadFactor = 1.0 * occupiedEntry / capacity;
            return occupiedEntry != 0 && capacity > 16 && (loadFactor < 0.3 || loadFactor > 0.75);
        }
        void resize();

        /** size is the number of inserted items. **/
        size_t size;
        /** occupied_entry is the number of entries or buckets occupied in the Object.**/
        /** capacity is the total number of available buckets or entries.**/
        size_t capacity, occupiedEntry;
        double loadFactor;
        Node **p;
    };
};
#endif