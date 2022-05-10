#include "atomjson.h"

namespace AtomJson
{
    namespace AtomJsonType
    {
        String::String(size_t len)
        {
            size = 0;
            if (len < 10)
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

        char &String::operator[](size_t pos)
        {
            assert(pos < size);
            return p[pos];
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

                char *np = new char[capacity];

                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete p;
                p = np;
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

                char *np = new char[capacity];

                for (size_t i = 0; i < size; i++)
                {
                    np[i] = p[i];
                }
                delete p;
                p = np;
            }

            for (size_t i = 0; i < len; i++)
            {
                p[size + i] = other[pos + i];
            }
            size += len;
            return *this;
        }

        std::ostream &operator<<(std::ostream &out, const String &str)
        {
            out << str.p;
            return out;
        }

        Array::Array(size_t len)
        {
            size = 0;
            if (len < 10)
                capacity = 10;
            else
                capacity = len;
            p = new Value[capacity];
        }

        Value::Value(const Value &other)
        {
            type = other.type;
            switch (type)
            {
            case BOOLEN:
                val.boolen = other.val.boolen;
                break;
            case NUMBER:
                val.num = other.val.num;
                break;
            case STRING:
                val.str = other.val.str;
                break;
            default:
                break;
            }
        }

        Value::Value(Value &&other)
        {
            type = other.type;
            switch (type)
            {
            case BOOLEN:
                val.boolen = other.val.boolen;
                break;
            case NUMBER:
                val.num = other.val.num;
                break;
            case STRING:
                val.str = std::move(other.val.str);
                break;
            default:
                break;
            }
        }

        Value::~Value()
        {
            switch (type)
            {
            case BOOLEN:
            case NUMBER:
                break;
            case STRING:
                val.str.~String();
                break;
            default:
                break;
            }
        };
    } // namespace  AtomJsonType

    Json::ParseRes Json::parse(const char *jsonstr)
    {
        ParseContext c(jsonstr);
        type = AtomJsonType::Type::_NULL;
        ParseRes ret;
        if ((ret = parse(&c)) == ParseRes::PARSE_OK)
        {
            parse_whitespace(&c);
            if (*c.json != '\0')
                ret = ParseRes::PARSE_ROOT_NOT_SINGULAR;
        }
        return ret;
    }

    Json::ParseRes Json::parse(ParseContext *c)
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

    Json::ParseRes Json::parse_whitespace(ParseContext *c)
    {
        const char *p = c->json;
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
            p++;
        c->json = p;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_null(ParseContext *c)
    {
        if (c->json[0] != 'n' || c->json[1] != 'u' || c->json[2] != 'l' || c->json[3] != 'l')
            return ParseRes::PARSE_INVALID_VALUE;
        c->json += 4;
        type = AtomJsonType::_NULL;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_boolen(ParseContext *c)
    {
        if (c->json[0] == 't')
        {
            if (c->json[1] != 'r' || c->json[2] != 'u' || c->json[3] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 4;
            type = AtomJsonType::BOOLEN;
            this->val.boolen = true;
        }
        else if (c->json[0] == 'f')
        {
            if (c->json[1] != 'a' || c->json[2] != 'l' || c->json[3] != 's' || c->json[4] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 5;
            type = AtomJsonType::BOOLEN;
            this->val.boolen = false;
        }
        else
            return ParseRes::PARSE_INVALID_VALUE;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_string(ParseContext *c)
    {
        const char *p = c->json;
        p += 1;
        AtomJsonType::String s(10);
        while (1)
        {
            char ch = *p;
            switch (*p++)
            {
            case '\"':
                //更新jsonstr
                c->json = p;
                this->val.str = std::move(s);
                type = AtomJsonType::Type::STRING;
                return ParseRes::PARSE_OK;
            case '\\':
            {
                switch (*p++)
                {
                case '\"':
                    s.append('\"');
                    break;
                case '\\':
                    s.append('\\');
                    break;
                case '/':
                    s.append('/');
                    break;
                case 'b':
                    s.append('\b');
                    break;
                case 'f':
                    s.append('\f');
                    break;
                case 'n':
                    s.append('\n');
                    break;
                case 'r':
                    s.append('\r');
                    break;
                case 't':
                    s.append('\t');
                    break;
                default:
                    return ParseRes::PARSE_INVALID_STRING_ESCAPE;
                }
                break;
            }
            case '\0':
                return ParseRes::PARSE_MISS_QUOTATION_MARK;
            default:
                if ((unsigned char)ch < 0x20)
                {
                    std::cout << ch << std::endl;
                    return ParseRes::PARSE_INVALID_STRING_CHAR;
                }
                s.append(ch);
            }
        }
    }

}
