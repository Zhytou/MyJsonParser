#pragma once
#ifndef ATOMJSON_HPP
#define ATOMJSON_HPP
#include <iostream>
#include <assert.h>
#include <cstring>
#include <string>
#include <vector>

#include "String.hpp"
#include "Array.hpp"
#include "Object.hpp"

namespace AtomJson
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

    struct Value
    {
        union SubValue
        {
            Boolen boolen;
            Number num;
            String str;
            Array arr;
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
         * @brief
         *
         * @param other
         * @return Value&
         */
        Value &operator=(const Value &other);

        /**
         * @brief
         *
         * @param other
         * @return Value&
         */
        Value &operator=(Value &&other);

        /**
         * @brief Destroy the Value object
         *
         */
        ~Value();

        /**
         * @brief
         *
         * @return bool
         */
        bool isNull() { return type == Type::_NULL; }

        /**
         * @brief
         *
         * @return bool
        bool isBoolen() { return type == Type::BOOLEN; }

        /**
         * @brief
         *
         * @return bool
         */
        bool isNumber() { return type == Type::NUMBER; }

        /**
         * @brief
         *
         * @return bool
         */
        bool isString() { return type == Type::STRING; }

        /**
         * @brief
         *
         * @return bool
         */
        bool isArray() { return type == Type::ARRAY; }

        /**
         * @brief
         *
         * @return bool
         */
        bool isObject() { return type == Type::OBJECT; }

        /**
         * @brief
         *
         * @param idx
         * @return Value&
         */
        Value &operator[](size_t idx);

        /**
         * @brief
         *
         * @param key
         * @return Value&
         */
        Value &operator[](String key);
    };

    class Json : Value
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

        Json() : Value(){};

        /**
         * @brief
         *
         * @param jsonstr
         * @return ParseRes
         */
        ParseRes parse(const char *jsonstr);
        void stringify();

    private:
        ParseRes parse(ParseContext *c);

        ParseRes parse_whitespace(ParseContext *c);

        ParseRes parse_null(ParseContext *c);

        ParseRes parse_boolen(ParseContext *c);

        ParseRes parse_number(ParseContext *c);

        ParseRes parse_string(ParseContext *c);

        ParseRes parse_array(ParseContext *c);
    };

} // namespace AtomJson

#endif
