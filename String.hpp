#ifndef ATOMJSON_STRING_HPP
#define ATOMJSON_STRING_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <functional>

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
         * @param len | the initial len of the Sting object
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
         * * STL string constructor
         * @brief Construct a new String object by a '\0' terminated C style string
         *
         * @param other
         */
        String(const std::string &other);

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
        bool empty() const { return size == 0 && p == nullptr; }

        /**
         * @brief Get the length of the String object
         *
         * @return size_t
         */
        size_t length() const { return size; }

        size_t hashcode() const
        {
            std::hash<std::string> h;
            return h(stl_str());
        }

        /**
         * *Overload array index operator
         * @brief Get the char at the idx
         *
         * @param pos
         * @return char&
         */
        char &operator[](size_t idx);

        /**
         * *Overload array index operator
         * @brief Get the char at the idx
         *
         * @param idx
         * @return const char&
         */
        const char &operator[](size_t idx) const;

        /**
         * *Overload equal to operator
         * @brief Check if the String object equals to the C-style string
         *
         * @param other
         * @return bool
         */
        bool operator==(const char *other) const;

        /**
         * *Overload equal to operator
         * @brief Check if every char in both of the String objects are the same
         *
         * @param other
         * @return bool
         */
        bool operator==(const String &other) const;

        /**
         * @brief
         *
         * @param other
         * @return String&
         */
        String &operator+=(const String &other);

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
         * @brief Add a substring of a C style string to the tail of the String object
         *
         * @param other
         * @param pos
         * @param len
         * @return String&
         */
        String &append(const char *other, size_t pos = 0, size_t len = 1);

        /**
         * @brief Add a substring of another String object to the tail of the String object
         *
         * @param other
         * @param pos
         * @param len
         * @return String&
         */
        String &append(const String &other, size_t pos = 0, size_t len = 1);

        /**
         * @brief Pop out the last char in String
         *
         */
        void pop()
        {
            assert(size >= 1);
            size -= 1;
        }

        /**
         * @brief Get a std::string
         *
         * @return std::string
         */
        std::string stl_str() const
        {
            std::string s;
            for (size_t i = 0; i < size; i++)
            {
                s.push_back(p[i]);
            }
            return s;
        }

        /**
         * ! The returned char* should be freed by user himself, otherwise memory will leak
         * @brief Get a C style string
         *
         * @return const char*
         */
        const char *c_str() const
        {
            char *s = new char[size + 1];
            for (size_t i = 0; i < size; i++)
                s[i] = p[i];
            s[size] = '\0';
            return s;
        }

    private:
        size_t size, capacity;
        char *p;
    };

};

#endif