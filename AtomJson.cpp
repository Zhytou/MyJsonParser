#include "AtomJson.hpp"

namespace AtomJson
{
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
        case ARRAY:
            val.arr = other.val.arr;
            break;
        case OBJECT:
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
        case ARRAY:
            val.arr = std::move(other.val.arr);
            break;
        case OBJECT:
            break;
        default:
            break;
        }
    }

    Value &Value::operator=(const Value &other)
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
        case ARRAY:
            val.arr = other.val.arr;
            break;
        case OBJECT:
            break;
        default:
            break;
        }

        return *this;
    }

    Value &Value::operator=(Value &&other)
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
        case ARRAY:
            val.arr = std::move(other.val.arr);
            break;
        case OBJECT:
            break;
        default:
            break;
        }

        return *this;
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

    Json::ParseRes Json::parse(const char *jsonstr)
    {
        ParseContext c(jsonstr);
        type = Type::_NULL;
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
        case '[':
            return parse_array(c);
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
        type = Type::_NULL;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_boolen(ParseContext *c)
    {
        if (c->json[0] == 't')
        {
            if (c->json[1] != 'r' || c->json[2] != 'u' || c->json[3] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 4;
            type = Type::BOOLEN;
            this->val.boolen = true;
        }
        else if (c->json[0] == 'f')
        {
            if (c->json[1] != 'a' || c->json[2] != 'l' || c->json[3] != 's' || c->json[4] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 5;
            type = Type::BOOLEN;
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
        String s(10);
        while (1)
        {
            char ch = *p;
            switch (*p++)
            {
            case '\"':
                //更新jsonstr
                c->json = p;
                this->val.str = std::move(s);
                type = Type::STRING;
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

    Json::ParseRes Json::parse_array(ParseContext *c)
    {
        return ParseRes::PARSE_OK;
    }
}
