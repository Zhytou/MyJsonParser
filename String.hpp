#ifndef ATOMJSON_STRING_HPP
#define ATOMJSON_STRING_HPP
#include <iostream>

namespace AtomJson
{
    /**
     * @brief
     *
     */
    class String
    {
    public:
        /**
         * * Default constructor
         * @brief Construct a new String object
         *
         * @param len
         */
        String(size_t len = 0);

        /**
         * * C-style string constructor
         * @brief Construct a new String object by a '\0' terminated C style string
         *
         * @param other
         */
        String(const char *other);

        /**
         * * Copy constructor
         * @brief Construct a new String object by another String object
         *
         * @param other
         */
        String(const String &other);

        /**
         * * Move constructor
         * @brief Construct a new String object by moving another String object
         *
         * @param other
         */
        String(String &&other);

        /**
         * * Copy assignment operator
         * @brief Assign a new String object by another String object
         *
         * @param other
         */
        String &operator=(const String &other);

        /**
         * * Move assignment operator
         * @brief Assign a new String object by moving another String object
         *
         * @param other
         */
        String &operator=(String &&other);

        /**
         * * Destructor
         * @brief Destroy the String object
         *
         */
        ~String();

        /**
         * @brief Check if the String object is null
         *
         * @return bool
         */
        bool empty() { return size == 0 && p == nullptr; }

        /**
         * @brief Get the length of the String object
         *
         * @return size_t
         */
        size_t length() { return size; }

        /**
         * *Overload array index operator
         * @brief Get the char at the idx
         *
         * @param pos
         * @return char&
         */
        char &operator[](size_t idx);

        /**
         * *Overload equal to operator
         * @brief Check if every char in both of the String objects are the same
         *
         * @param other
         * @return bool
         */
        bool operator==(const String &other);

        /**
         * *Overload the output operator
         * @brief Insert the String object into the standard template library outstream
         *
         * @param out
         * @param str
         * @return std::ostream&
         */
        friend std::ostream &operator<<(std::ostream &out, const String &str);

        /**
         * @brief Add a char to the tail of the String object
         *
         * @param ch
         * @return String&
         */
        String &append(char ch);

        /**
         * @brief Add a substring of another String object to the tail of the String object
         *
         * @param other
         * @param pos
         * @param len
         * @return String&
         */
        String &append(String &other, size_t pos = 0, size_t len = 1);

    private:
        size_t size, capacity;
        char *p;
    };

};

#endif