#pragma once
#ifndef ATOMJSON_H
#define ATOMJSON_H

namespace AtomJson
{
    namespace AtomJsonType
    {
        enum Type
        {
            NULL,
            BOOLEN,
            NUMBER,
            STRING,
            ARRAY,
            OBJECT
        };
        struct Value
        {
            union
            {
                Boolen b;
                Number n;
                String s;
                // Array *a;
                // Object *o;
            } val;
            Type type;
        };

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
            // String(String &other) = delete;

        private:
            char *s;
            size_t size, capacity;
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

            Object() : capacity(1)
            {
                pairs = new Pair[capacity];
            }
            Object(size_t s)
            {
                size = s;
                capacity = 1.5 * size;
                pairs = new Pair[capacity];
            }
            Value &operator[](char *key);

        private:
            Pair *pairs;
            size_t size, capacity;
        };

    };

    class Json
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
        ParseRes parse(const char *jsonstr)
        {
            ParseContext c(jsonstr);
            v.type = AtomJsonType::Type::NULL;
            ParseRes ret;
            if ((ret = parse(&c)) == ParseRes::PARSE_OK)
            {
                parse_whitespace(&c);
                if (*c.json != '\0')
                    ret = ParseRes::PARSE_ROOT_NOT_SINGULAR;
            }
            return ret;
        };
        void stringify();

    private:
        ParseRes parse(ParseContext *c)
        {
            switch (*c->json)
            {
            case 'n':
                return parse_null(c);
            case 't':
            case 'f':
                return parse_boolen(c);

            case '\"':
                return parse_string(c);

            case '\0':
                return PARSE_EXPECT_VALUE;
            default:
                return PARSE_INVALID_VALUE;
            };
        }

        ParseRes parse_whitespace(ParseContext *c)
        {
            const char *p = c->json;
            while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
                p++;
            c->json = p;
        }

        ParseRes parse_null(ParseContext *c)
        {
            if (c->json[0] != 'n' || c->json[1] != 'u' || c->json[2] != 'l' || c->json[3] != 'l')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 4;
            v.type = AtomJsonType::NULL;
            return ParseRes::PARSE_OK;
        }

        ParseRes parse_boolen(ParseContext *c)
        {
            if (c->json[0] == 't')
            {
                if (c->json[1] != 'r' || c->json[2] != 'u' || c->json[3] != 'e')
                    return ParseRes::PARSE_INVALID_VALUE;
                c->json += 4;
                v.type = AtomJsonType::BOOLEN;
                v.val.b = true;
            }
            else if (c->json[0] == 'f')
            {
                if (c->json[1] != 'a' || c->json[2] != 'l' || c->json[3] != 's' || c->json[4] != 'e')
                    return ParseRes::PARSE_INVALID_VALUE;
                c->json += 5;
                return ParseRes::PARSE_INVALID_VALUE;
                v.type = AtomJsonType::BOOLEN;
                v.val.b = false;
            }
            else
                return ParseRes::PARSE_INVALID_VALUE;
            return ParseRes::PARSE_OK;
        }

        ParseRes parse_string(ParseContext *c)
        {
        }

        AtomJsonType::Value v;
    };

} // namespace AtomJson

#endif
