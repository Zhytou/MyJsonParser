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
            String() : size(0), capacity(0), s(nullptr){};
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
            String(String &other) = delete;

            ~String()
            {
                delete s;
                size = 0;
                capacity = 0;
            }

        private:
            char *s;
            size_t size, capacity;
        };

        struct Value
        {
            union RealValue
            {
                Boolen b;
                Number n;
                String s;
                // Array *a;
                // Object *o;

                RealValue(){};
                ~RealValue() {}
            } val;
            Type type;

            Value() : type(_NULL){};
            ~Value(){};
        };

        class Array
        {
        public:
            Value &operator[](size_t idx);

        private:
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
            PARSE_ROOT_NOT_SINGULAR
        };
        struct ParseContext
        {
            const char *json;

            ParseContext() : json(nullptr){};
            ParseContext(const char *s) : json(s){};
        };

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
        Json() : AtomJsonType::Value(){};
        // void stringify();
        bool isEmpty() { return type == AtomJsonType::Type::_NULL; }
        bool isBoolen() { return type == AtomJsonType::Type::BOOLEN; }
        bool isNumber() { return type == AtomJsonType::Type::NUMBER; }

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
