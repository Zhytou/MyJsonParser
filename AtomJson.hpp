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
#include "Buffer.hpp"

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
            Object obj;

            /**
             * *Default constructor
             * @brief Construct a new Sub Value object
             *
             */
            SubValue() { std::memset(this, 0, sizeof(SubValue)); }

            /**
             * @brief Construct a new SubValue object by copying a Boolen object
             *
             * @param b
             */
            SubValue(const Boolen &b)
            {
                std::memset(this, 0, sizeof(SubValue));
                boolen = b;
            }

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
                str = s;
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
                arr = a;
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
                obj = o;
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

            /***/
            SubValue &operator=(SubValue &&other)
            {
                std::memcpy(this, &other, sizeof(SubValue));
                return *this;
            }

            /**
             * @brief Destroy the Sub Value object
             *
             */
            ~SubValue()
            {
                // Because the allocated dynamic memory for str/arr/obj is already freed in ~Value(), so there is nothing to do in ~SubValue()
            }
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
         * @param t
         * @param b
         */
        Value(const Boolen &b, Type t = Type::BOOLEN) : type(t), val(b) {}

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
        bool isNull() { return type == Type::_NULL; }

        /**
         * @brief
         *
         * @return bool
         */
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
         * @brief Set the Value object to NULL
         *
         */
        void setNull();

        /**
         * @brief Get the Boolen object
         *
         * @return Boolen&
         */
        Boolen &getBoolen()
        {
            assert(isBoolen());
            return val.boolen;
        }

        /**
         * @brief Set the Boolen object
         *
         * @param b
         */
        void setBoolen(Boolen b)
        {
            assert(isBoolen());
            val.boolen = b;
        }

        /**
         * @brief Get the Number object
         *
         * @return Number&
         */
        Number &getNumber()
        {
            assert(isNumber());
            return val.num;
        }

        /**
         * @brief Set the Number object
         *
         * @param n
         */
        void setNumber(Number n)
        {
            assert(isNumber());
            val.num = n;
        }

        /**
         * @brief Get the String object
         *
         * @return String&
         */
        String &getString()
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
         * *Overload the index array operator
         * @brief Get the element in the idx position of the Value object only if the Value type is ARRAY
         *
         * @param idx
         * @return Value&
         */
        Value &operator[](size_t idx);

        /**
         * *Overload the reference operator
         * @brief Get the element whose key eaquls to the param in the Value object only if the Value type is OBJECT
         *
         * @param key
         * @return Value&
         */
        Value &operator[](String key);
    };

    class Json : public Value
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
            PARSE_INVALID_STRING_ESCAPE,

            PARSE_MISS_SQUARE_BRACKET,
        };

        struct ParseContext
        {
            const char *jsonstr;
            Buffer buffer;

            ParseContext() : jsonstr(nullptr), buffer(){};

            ParseContext(const char *s) : jsonstr(s), buffer(){};
        };

        /**
         * *Default constructor
         * @brief Construct a new Json object
         *
         */
        Json() : Value(){};

        /**
         * *Copy constructor
         * @brief Construct a new Json object by Value object
         *
         * @param other
         */
        Json(const Value &other) : Value(other) {}

        /**
         * *Copy constructor
         * @brief Construct a new Json object
         *
         * @param other
         */
        Json(const Json &other) : Value(other.val, other.type) {}

        /**
         * *Destructor
         * @brief Destroy the Json object
         *
         */
        ~Json()
        {
        }

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

        ParseRes parse_object(ParseContext *c);
    };

} // namespace AtomJson

#endif
