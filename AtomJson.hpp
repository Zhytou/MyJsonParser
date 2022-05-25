#pragma once
#ifndef ATOMJSON_HPP
#define ATOMJSON_HPP
#include <iostream>
#include <assert.h>
#include <cstring>
#include <string>
#include <vector>

#include "Number.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "Object.hpp"

namespace AtomJson
{

    enum ParseRes
    {
        PARSE_OK,
        PARSE_EXPECT_VALUE,
        PARSE_INVALID_VALUE,
        PARSE_ROOT_NOT_SINGULAR,

        PARSE_INVALID_ZERO_START,
        PARSE_INVALID_SCIENTIFIC_NOTATION,
        PARSE_NUMBER_OVERFLOW,

        PARSE_STRING_MISS_QUOTATION_MARK,
        PARSE_STRING_INVALID_STRING_CHAR,
        PARSE_STRING_INVALID_STRING_ESCAPE,

        PARSE_ARRAY_INVALID_COMMA,
        PARSE_ARRAY_MISS_SQUARE_BRACKET,

        PARSE_OBJECT_MISS_COLON,
        PARSE_OBJECT_INVALID_COMMA,
        PARSE_OBJECT_INVALID_VALUE,
        PARSE_OBJECT_MISS_BRACKET
    };

    struct ParseContext
    {
        const char *jsonstr;

        ParseContext() : jsonstr(nullptr){};

        ParseContext(const char *s) : jsonstr(s){};

        ~ParseContext(){};
    };

    struct StringifyParam
    {
        /** the prettify concerning params **/
        bool prettify;
        size_t indentation;

        /** the num to string concerning params **/
        bool scientificNotation;
        size_t customPrecision;

        /** the string to string concerning params **/
        bool keepEscape;

        StringifyParam(bool p = false, bool s = false, size_t cp = 0, bool k = false) : prettify(p), indentation(0), scientificNotation(s), customPrecision(cp), keepEscape(k){};

        ~StringifyParam(){};
    };

    enum Type
    {
        _NULL,
        TRUE,
        FALSE,
        NUMBER,
        STRING,
        ARRAY,
        OBJECT
    };

    class Value
    {

        union SubValue
        {
            Number num;
            String str;
            Array arr;
            Object obj;

            /**
             * *Default constructor
             * @brief Construct a new Sub Value object
             *
             */
            SubValue() { std::memset(this, 0, sizeof(SubValue)); }

            /**
             * @brief Construct a new Sub Value object by copying a Number object
             *
             * @param n
             */
            SubValue(const Number &n)
            {
                std::memset(this, 0, sizeof(SubValue));
                num = n;
            }

            /**
             * @brief Construct a new Sub Value object by copying a String object
             *
             * @param s
             */
            SubValue(const String &s)
            {
                std::memset(this, 0, sizeof(SubValue));
                str = s;
            }

            /**
             * @brief Construct a new Sub Value object by moving a String object
             *
             * @param s
             */
            SubValue(String &&s)
            {
                std::memset(this, 0, sizeof(SubValue));
                str = std::move(s);
            }

            /**
             * @brief Construct a new Sub Value object by copying an Array object
             *
             * @param a
             */
            SubValue(const Array &a)
            {
                std::memset(this, 0, sizeof(SubValue));
                arr = a;
            }

            /**
             * @brief Construct a new Sub Value object
             *
             * @param a
             */
            SubValue(Array &&a)
            {
                std::memset(this, 0, sizeof(SubValue));
                arr = std::move(a);
            }

            /**
             * @brief Construct a new Sub Value object
             *
             * @param o
             */
            SubValue(const Object &o)
            {
                std::memset(this, 0, sizeof(SubValue));
                obj = o;
            }

            /**
             * @brief Construct a new Sub Value object
             *
             * @param o
             */
            SubValue(Object &&o)
            {
                std::memset(this, 0, sizeof(SubValue));
                obj = std::move(o);
            }

            SubValue(const SubValue &other) = delete;

            /**
             * @brief
             *
             * @param other
             * @return SubValue&
             */
            SubValue &
            operator=(const SubValue &other) = delete;

            /**
             * @brief
             *
             * @param other
             * @return SubValue&
             */
            SubValue &operator=(SubValue &&other)
            {
                std::memcpy(this, &other, sizeof(SubValue));
                return *this;
            }

            /**
             * @brief Destroy the Sub Value object
             * Because the allocated dynamic memory for str/arr/obj is already freed in ~Value(), so there is nothing to do in ~SubValue()
             */
            ~SubValue() {}
        };

    public:
        /**
         * @brief Construct a new Value object
         *
         */
        Value() : type(_NULL), val(){};

        /**
         * @brief Construct a new Value object
         *
         * @param b
         */
        Value(const bool &b)
        {
            if (b)
                type = Type::TRUE;
            else
                type = Type::FALSE;
        }

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param i
         */
        Value(const int &i, Type t = Type::NUMBER) : type(t), val(Number(i)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param l
         */
        Value(const long &l, Type t = Type::NUMBER) : type(t), val(Number(l)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param u
         */
        Value(const unsigned &u, Type t = Type::NUMBER) : type(t), val(Number(u)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param ul
         */
        Value(const unsigned long &ul, Type t = Type::NUMBER) : type(t), val(Number(ul)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param f
         */
        Value(const float &f, Type t = Type::NUMBER) : type(t), val(Number(f)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param d
         */
        Value(const double &d, Type t = Type::NUMBER) : type(t), val(Number(d)) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param n
         */
        Value(const Number &n, Type t = Type::NUMBER) : type(t), val(n) {}

        /**
         * @brief Construct a new Value object
         *
         * @param s
         * @param t
         */
        Value(const char *s, Type t = Type::STRING) : type(t), val(std::move(String(s))) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param s
         */
        Value(const String &s, Type t = Type::STRING) : type(t), val(s) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param s
         */
        Value(String &&s, Type t = Type::STRING) : type(t), val(s) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param a
         */
        Value(const Array &a, Type t = Type::ARRAY) : type(t), val(a) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param a
         */
        Value(Array &&a, Type t = Type::ARRAY) : type(t), val(a) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param o
         */
        Value(const Object &o, Type t = Type::OBJECT) : type(t), val(o) {}

        /**
         * @brief Construct a new Value object
         *
         * @param t
         * @param o
         */
        Value(Object &&o, Type t = Type::OBJECT) : type(t), val(o) {}

        /**
         * @brief Construct a new Value object
         *
         * @param v
         * @param t
         */
        Value(const SubValue &v, Type t);

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
        bool isNull() const
        {
            return type == Type::_NULL;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isBoolen() const
        {
            return type == Type::TRUE || type == Type::FALSE;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isTrue() const
        {
            return type == Type::TRUE;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isFalse() const
        {
            return type == Type::FALSE;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isNumber() const
        {
            return type == Type::NUMBER;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isString() const
        {
            return type == Type::STRING;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isArray() const
        {
            return type == Type::ARRAY;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool isObject() const
        {
            return type == Type::OBJECT;
        }

        /**
         * @brief
         *
         * @return size_t
         */
        size_t length() const
        {
            assert(isNull() || isString() || isArray() || isObject());
            switch (type)
            {
            case Type::_NULL:
                return 0;
            case Type::STRING:
                return val.str.length();
            case Type::ARRAY:
                return val.arr.length();
            case Type::OBJECT:
                return val.obj.length();
            default:
                return -1;
            }
        }

        /**
         * @brief Set the Value object to NULL
         *
         */
        void setNull();

        /**
         * @brief Set the Boolen object
         *
         * @param b
         */
        void setBoolen(const bool &b)
        {
            assert(isBoolen());
            if (b)
                type = Type::TRUE;
            else
                type = Type::FALSE;
        }

        /**
         * @brief Get the Number object
         *
         * @return Number&
         */
        const Number &getNumber() const
        {
            assert(isNumber());
            return val.num;
        }

        /**
         * @brief Set the Number object
         *
         * @param n
         */
        void setNumber(const Number &n)
        {
            assert(isNumber());
            val.num = n;
        }

        /**
         * @brief Get the String object
         *
         * @return String&
         */
        const String &getString() const
        {
            assert(isString());
            return val.str;
        }

        /**
         * @brief Set the String object
         *
         * @param s
         */
        void setString(const String &s)
        {
            assert(isString());
            val.str = s;
        }

        /**
         * @brief Get the Array object
         *
         * @return const Array&
         */
        const Array &getArray() const
        {
            assert(isArray());
            return val.arr;
        }

        /**
         * @brief Get the Object object
         *
         * @return const Object&
         */
        const Object &getObject() const
        {
            assert(isObject());
            return val.obj;
        }

        /**
         * @brief Check if the key exist
         *
         * @param key
         * @return bool
         */
        bool exist(const String &key) const
        {
            assert(isObject());
            return val.obj.exist(key);
        }

        /**
         * @brief
         *
         * @return Array
         */
        Array keys() const
        {
            assert(isObject());
            return val.obj.keys();
        }

        /**
         * @brief
         *
         * @return Array
         */
        Array values() const
        {
            assert(isObject());
            return val.obj.values();
        }

        /**
         * *Overload the index array operator
         * @brief Get the element in the idx position of the Value object only if the Value type is ARRAY
         *
         * @param idx
         * @return Value&
         */
        Value &
        operator[](size_t idx);

        /**
         * *Overload the index array operator
         * @brief Get the element in the idx position of the Value object only if the Value type is ARRAY
         *
         * @param idx
         * @return const Value&
         */
        const Value &operator[](size_t idx) const;

        /**
         * *Overload the reference operator
         * @brief Get the element whose key eaquls to the param in the Value object only if the Value type is OBJECT
         *
         * @param key
         * @return const Value&
         */
        Value &operator[](const String &key);

        /**
         * *Overload the reference operator
         * @brief Get the element whose key eaquls to the param in the Value object only if the Value type is OBJECT
         *
         * @param key
         * @return const Value&
         */
        const Value &operator[](const String &key) const;

        /**
         * @brief Check if the two Value objects are the same
         *
         * @param other
         * @return bool
         */
        bool operator==(const Value &other);

        /**
         * @brief Check if the two Value objects are not the same
         *
         * @param other
         * @return bool
         */
        bool operator!=(const Value &other)
        {
            return !(this->operator==(other));
        }

        /**
         * @brief
         *
         * @param out
         * @return std::ostream
         */
        friend std::ostream &operator<<(std::ostream &out, const Value &v);

        /**
         * @brief
         *
         * @param jsonstr
         * @return Value
         */
        friend Value parse(const char *jsonstr);

        /**
         * @brief
         *
         * @param prettify
         * @return String
         */
        friend String stringify(const Value &v, bool prettify, bool scientificNotation, size_t customPrecision, bool keepEscape);

    private:
        ParseRes parse(ParseContext *c);

        String stringify(StringifyParam *p) const;

        friend ParseRes parse_whitespace(ParseContext *c);

        ParseRes parse_null(ParseContext *c);

        ParseRes parse_boolen(ParseContext *c);

        ParseRes parse_number(ParseContext *c);

        ParseRes parse_string(ParseContext *c);

        ParseRes parse_array(ParseContext *c);

        ParseRes parse_object(ParseContext *c);

        String stringify_null(StringifyParam *p) const;

        String stringify_boolen(StringifyParam *p) const;

        String stringify_number(StringifyParam *p) const;

        String stringify_string(StringifyParam *p) const;

        String stringify_array(StringifyParam *p) const;

        String stringify_object(StringifyParam *p) const;

        SubValue val;
        Type type;
    };
    typedef Value Json;

    /**
     * @brief
     *
     * @param jsonstr
     * @return Value
     */
    Value parse(const char *jsonstr);

    /**
     * @brief
     *
     * @param v
     * @param prettify
     * @param scientificNotation
     * @param customPrecision
     * @param keepEscape
     * @return String
     */
    String stringify(const Value &v, bool prettify = true, bool scientificNotation = false, size_t customPrecision = 2, bool keepEscape = false);
} // namespace AtomJson

namespace ajson = AtomJson;

#endif
