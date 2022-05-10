#pragma once
#ifndef ATOMJSON_H
#define ATOMJSON_H
#include <iostream>
#include <assert.h>
#include <cstring>
#include <string>
#include <vector>
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

        typedef bool Boolen;

        typedef double Number;

        /**
         * @brief
         *
         */
        class String
        {
        public:
            /**
             * @brief Construct a new String object
             *
             * @param len
             */
            String(size_t len = 10);

            /**
             * @brief Construct a new String object
             *
             * @param other
             */
            String(const char *other);

            /**
             * @brief Construct a new String object
             *
             * @param other
             */
            String(const String &other);

            /**
             * @brief Construct a new String object
             *
             * @param other
             */
            String(String &&other);

            /**
             * @brief String copy operator
             *
             * @param other
             */
            String &operator=(const String &other);

            /**
             * @brief Construct a new String object
             *
             * @param other
             */
            String &operator=(String &&other);

            /**
             * @brief Destroy the String object
             *
             */
            ~String();

            /**
             * @brief
             *
             * @return true
             * @return false
             */
            bool empty() { return size == 0; }

            /**
             * @brief Get the Size
             *
             * @return size_t
             */
            size_t length() { return size; }

            /**
             * @brief
             *
             * @param pos
             * @return char&
             */
            char &operator[](size_t pos);

            /**
             * @brief
             *
             * @param ch
             * @return String&
             */
            String &append(char ch);

            /**
             * @brief
             *
             * @param other
             * @param pos
             * @param len
             * @return String&
             */
            String &append(String &other, size_t pos = 0, size_t len = 1);

            friend std::ostream &operator<<(std::ostream &out, const String &str);

        private:
            size_t size, capacity;
            char *p;
        };

        struct Value;

        class Array
        {
        public:
            /**
             * @brief Construct a new Array object
             *
             * @param len
             */
            Array(size_t len = 10);

            /**
             * @brief Destroy the Array object
             *
             */
            ~Array();

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
             * @param idx
             * @return Value&
             */
            Value &operator[](size_t idx);

        private:
            size_t size, capacity;
            Value *p;
        };

        class Object
        {
        public:
            struct Pair
            {
                String key;
                Value *val;
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
            size_t size, capacity;
            Pair *p;
        };

        struct Value
        {
            union SubValue
            {
                Boolen boolen;
                Number num;
                String str;
                // Array arr;
                // Object obj;
                SubValue() { std::memset(this, 0, sizeof(SubValue)); }
                ~SubValue() {}
            } val;
            Type type;

            /**
             * @brief Construct a new Value object
             *
             */
            Value() : type(_NULL), val(){};

            /**
             * @brief Construct a new Value object
             *
             * @param other
             */
            Value(const Value &other);

            /**
             * @brief Construct a new Value object
             *
             * @param other
             */
            Value(Value &&other);

            /**
             * @brief Destroy the Value object
             *
             */
            ~Value();
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
        void stringify();

        bool isNull() { return type == AtomJsonType::Type::_NULL; }
        bool isBoolen() { return type == AtomJsonType::Type::BOOLEN; }
        bool isNumber() { return type == AtomJsonType::Type::NUMBER; }
        bool isString() { return type == AtomJsonType::Type::STRING; }

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
