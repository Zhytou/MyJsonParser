#include "AtomJson.hpp"
#include "String.hpp"

namespace AtomJson
{
    String::String(size_t len)
    {
        assert(len >= 0);
        size = len;
        // capacity adds 2 to avoid the case that length equals 1 or 0 and capacity will always be 1
        capacity = 1.5 * len + 2;
        p = new char[capacity];
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

    String::String(String &&other)
    {
        size = other.size;
        capacity = other.capacity;
        p = other.p;

        other.size = 0;
        other.capacity = 0;
        other.p = nullptr;
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

    const char &String::operator[](size_t idx) const
    {
        assert(idx < size);
        return p[idx];
    }

    bool String::operator==(const char *other) const
    {
        for (size_t i = 0; i < size; i++)
        {
            if (p[i] != other[i] || other[i] == '\0')
                return false;
        }
        return other[size] == '\0';
    }

    bool String::operator==(const String &other) const
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
                if (capacity == 0 || capacity == 1)
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

    String &String::append(const char *other, size_t pos, size_t len)
    {
        for (size_t i = 0; i < len; i++)
            assert(other[pos + i] != '\0');

        if (size + len >= capacity)
        {
            do
            {
                if (capacity == 0 || capacity == 1)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + len >= capacity);

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

    String &String::append(const String &other, size_t pos, size_t len)
    {
        assert(pos + len - 1 < other.size);
        if (size + len >= capacity)
        {
            do
            {
                if (capacity == 0 || capacity == 1)
                    capacity = 10;
                else
                    capacity = 1.5 * capacity;
            } while (size + len >= capacity);

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

} // namespace AtomJson
