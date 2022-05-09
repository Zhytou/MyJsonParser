#pragma once
#ifndef ATOMJSON_H
#define ATOMJSON_H
#include <iostream>
#include <assert.h>
namespace AtomJson
{
    namespace AtomJsonType
    {
        enum Type
        {
            _NULL,
            BOOLEN,
            NUMBER,
            STRING,
            ARRAY,
            OBJECT
        };

        typedef bool Null;

        typedef bool Boolen;

        typedef double Number;

        class String
        {
        public:
            String()
            {
                size = 0;
                capacity = 10;
                s = new char[capacity];
            }

            String(const char *other)
            {
                size = 0;
                while (other[size] != '\0')
                    size += 1;
                capacity = 1.5 * size;
                if (size == 0)
                    s = nullptr;
                else
                {
                    s = new char[capacity];
                    for (size_t i = 0; i < size; i++)
                        s[i] = other[i];
                }
            }

            String(const String &other)
            {
                size = other.size;
                capacity = other.capacity;
                s = new char[capacity];

                for (size_t i = 0; i < size; i++)
                    s[i] = other.s[i];
            }

            String &operator=(const String &other)
            {
                if (s)
                    delete s;
                size = other.size;
                capacity = other.capacity;
                s = new char[capacity];

                for (size_t i = 0; i < size; i++)
                    s[i] = other.s[i];
                return *this;
            }

            String &operator=(String &&other)
            {
                if (s)
                    delete s;
                s = other.s;
                size = other.size;
                capacity = other.capacity;
                other.s = nullptr;
                other.size = 0;
                other.capacity = 0;
                return *this;
            }

            ~String()
            {
                delete s;
                size = 0;
                capacity = 0;
            }

            bool isEmpty() { return size == 0; }
            size_t getSize() { return size; }

            char &operator[](size_t pos)
            {
                assert(pos < size);
                return s[pos];
            }

            String &append(char ch)
            {
                while (size + 1 >= capacity)
                {
                    capacity = 1.5 * capacity;
                }
                char *ns = new char[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    ns[i] = s[i];
                }
                delete s;
                s = ns;
                s[size] = ch;
                size += 1;
                return *this;
            }

            String &append(String &other, size_t pos = 0, size_t len = 1)
            {
                assert(pos + len < other.size);
                while (size + len >= capacity)
                {
                    capacity = 1.5 * capacity;
                }
                char *ns = new char[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    ns[i] = s[i];
                }
                delete s;
                s = ns;
                for (size_t i = 0; i < len; i++)
                {
                    s[i] = other[pos + i];
                }
                size += len;
                return *this;
            }

            friend std::ostream &operator<<(std::ostream &out, const String &str);

        private:
            char *s;
            size_t size, capacity;
        };

        std::ostream &operator<<(std::ostream &out, const String &str)
        {
            out << str.s;
            return out;
        }

        struct Value
        {
            union SubValue
            {
                Boolen b;
                Number n;
                String s;
                // Array *a;
                // Object *o;

                SubValue(){};
                ~SubValue(){};
            } val;
            Type type;

            Value() : type(_NULL){};

            Value(const Value &other)
            {
                type = other.type;
                switch (type)
                {
                case BOOLEN:
                    val.b = other.val.b;
                    break;
                case NUMBER:
                    val.n = other.val.n;
                    break;
                case STRING:
                    val.s = other.val.s;
                    break;
                default:
                    break;
                }
            }

            Value(Value &&other)
            {
                type = other.type;
                switch (type)
                {
                case BOOLEN:
                    val.b = other.val.b;
                    break;
                case NUMBER:
                    val.n = other.val.n;
                    break;
                case STRING:
                    val.s = std::move(other.val.s);
                    break;
                default:
                    break;
                }
            }
            ~Value(){};
        };

        class Array
        {
        public:
            Value &operator[](size_t idx);

        private:
            Value *arr;
        };

        class Object
        {
        public:
            struct Pair
            {
                String key;
                Value val;
                Pair() = default;
            };

            Object()
            {
                capacity = 1;
                // pairs = new Pair[capacity];
            }
            Object(size_t s)
            {
                size = s;
                capacity = 1.5 * size;
                // pairs = new Pair;
            }
            Value &operator[](char *key);

        private:
            Pair *pairs;
            size_t size, capacity;
        };

    };

    class Json : private AtomJsonType::Value
    {
    public:
        enum ParseRes
        {
            PARSE_OK,
            PARSE_EXPECT_VALUE,
            PARSE_INVALID_VALUE,
            PARSE_ROOT_NOT_SINGULAR,

            PARSE_MISS_QUOTATION_MARK,
            PARSE_INVALID_STRING_CHAR,
            PARSE_INVALID_STRING_ESCAPE
        };
        struct ParseContext
        {
            const char *json;
            char *buffer;
            ParseContext() : json(nullptr), buffer(nullptr){};
            ParseContext(const char *s) : json(s){};
        };

        Json() : AtomJsonType::Value(){};

        /*
        n ➔ null
        t ➔ true
        f ➔ false
        " ➔ string
        0-9/- ➔ number
        [ ➔ array
        { ➔ object
        */
        ParseRes parse(const char *jsonstr);
        // void stringify();
        bool isEmpty() { return type == AtomJsonType::Type::_NULL; }
        bool isBoolen() { return type == AtomJsonType::Type::BOOLEN; }
        bool isNumber() { return type == AtomJsonType::Type::NUMBER; }
        bool isString() { return type == AtomJsonType::Type::STRING; }

        AtomJsonType::String getString()
        {
            assert(isString());
            return val.s;
        }

    private:
        ParseRes parse(ParseContext *c);

        ParseRes parse_whitespace(ParseContext *c);

        ParseRes parse_null(ParseContext *c);

        ParseRes parse_boolen(ParseContext *c);

        ParseRes parse_number(ParseContext *c);

        ParseRes parse_string(ParseContext *c);
    };

} // namespace AtomJson

#endif
