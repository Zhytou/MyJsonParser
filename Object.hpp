#ifndef ATOMJSON_OBJECT_HPP
#define ATOMJSON_OBJECT_HPP

#include <iostream>

namespace AtomJson
{
    struct Value;

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
             * *Copy constructor
             * @brief Construct a new Item object by copying another Item object
             *
             * @param other
             */
            Item(const Item &other)
            {
                key = other.key;
                val = new Value(*other.val);
            }

            /**
             * *Move constructor
             * @brief Construct a new Item object by moving another Item object
             *
             * @param other
             */
            Item(Item &&other)
            {
                key = std::move(other.key);
                val = other.val;
                other.val = nullptr;
            }

            /**
             * *Copy assignment operator
             * @brief Assign a new Item object by another Item object
             *
             * @param other
             * @return Item&
             */
            Item &operator=(const Item &other)
            {
                key = other.key;
                val = new Value(*other.val);
                return *this;
            }

            /**
             * *Move assignment operator
             * @brief Assign a new Item object by moving another Item object
             *
             * @param other
             * @return Item&
             */
            Item &operator=(Item &&other)
            {
                key = std::move(other.key);
                val = other.val;
                other.val = nullptr;
                return *this;
            }

            /**
             * *Destructor
             *  @brief Destroy the Item object
             *
             */
            ~Item()
            {
                if (val)
                    delete val;
            }
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
        Value &operator[](const String &key);

        /**
         * @brief
         *
         * @param other
         * @return bool
         */
        bool operator==(const Object &other);

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