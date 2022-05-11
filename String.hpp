#ifndef ATOMJSON_STRING_HPP
#define ATOMJSON_STRING_HPP
#include "AtomJson.hpp"
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
         * @return true
         * @return false
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
         * @return true
         * @return false
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

    String::String(size_t len)
    {
        size = 0;
        if (len < 10 && len != 0)
            capacity = 10;
        else
            capacity = len;
        if (capacity)
            p = new char[capacity];
        else
            p = nullptr;
    }

    String::String(const char *other)
    {
        size = 0;
        while (other[size] != '\0')
            size += 1;
        capacity = 1.5 * size;
        if (size == 0)
            p = nullptr;
        else
        {
            p = new char[capacity];
            for (size_t i = 0; i < size; i++)
                p[i] = other[i];
        }
    }

    String::String(const String &other)
    {
        size = other.size;
        capacity = other.capacity;
        p = new char[capacity];

        for (size_t i = 0; i < size; i++)
            p[i] = other.p[i];
    }

    String &String::operator=(const String &other)
    {
        if (p)
            delete[] p;
        size = other.size;
        capacity = other.capacity;
        p = new char[capacity];

        for (size_t i = 0; i < size; i++)
            p[i] = other.p[i];
        return *this;
    }

    String &String::operator=(String &&other)
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

    String::~String()
    {
        if (p)
            delete[] p;
        p = nullptr;
        size = 0;
        capacity = 0;
    }

    char &String::operator[](size_t idx)
    {
        assert(idx < size);
        return p[idx];
    }

    bool String::operator==(const String &other)
    {
        if (size != other.size)
            return false;
        for (size_t i = 0; i < size; i++)
        {
            if (p[i] != other.p[i])
                return false;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &out, const String &str)
    {
        out << str.p;
        return out;
    }

    String &String::append(char ch)
    {
        if (size + 1 >= capacity)
        {
            do
            {
                if (capacity == 0)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + 1 >= capacity);

            if (p)
            {
                char *np = new char[capacity];

                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete[] p;
                p = np;
            }
            else
                p = new char[capacity];
        }

        p[size] = ch;
        size += 1;
        return *this;
    }

    String &String::append(String &other, size_t pos, size_t len)
    {
        assert(pos + len < other.size);
        if (size + len >= capacity)
        {
            do
            {
                if (capacity == 0)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + 1 >= capacity);

            if (p)
            {
                char *np = new char[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete[] p;
                p = np;
            }
            else
                p = new char[capacity];
        }

        for (size_t i = 0; i < len; i++)
        {
            p[size + i] = other[pos + i];
        }
        size += len;
        return *this;
    }

};

#endif