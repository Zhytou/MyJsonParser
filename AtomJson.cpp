#include "AtomJson.hpp"

namespace AtomJson
{
    Value::Value(const SubValue &v, Type t)
    {
        type = t;
        switch (type)
        {
        case BOOLEN:
        case NUMBER:
            std::memcpy(&val, &v, sizeof(SubValue));
            break;
        case STRING:
            val.str = v.str;
            break;
        case ARRAY:
            val.arr = v.arr;
            break;
        case OBJECT:
            break;
        default:
            std::memset(&val, 0, sizeof(SubValue));
            break;
        }
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

        // don't need this memset, because the val is calling String/Array/Object move constructor and they will set the bytes zero to make sure the dynamic memory is freed.
        // std::memset(&other, 0, sizeof(Value));
        // other.type = _NULL;
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

        // don't need this memset, because the val is calling String/Array/Object move constructor and they will set the bytes zero to make sure the dynamic memory is freed.
        // std::memset(&other, 0, sizeof(Value));
        // other.type = _NULL;

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
        case ARRAY:
            val.arr.~Array();
            break;
        case OBJECT:
            break;
        default:
            break;
        }
    };

    void Value::setNull()
    {
        switch (type)
        {
        case BOOLEN:
        case NUMBER:
            break;
        case STRING:
            val.str.~String();
            break;
        case ARRAY:
            val.arr.~Array();
            break;
        case OBJECT:
            val.obj.~Object();
            break;
        default:
            break;
        }
        type = _NULL;
    }

    Value &Value::operator[](size_t idx)
    {
        assert(isArray());
        return val.arr[idx];
    }

    Json::ParseRes Json::parse(const char *jsonstr)
    {
        ParseContext c(jsonstr);
        type = Type::_NULL;
        ParseRes ret;

        parse_whitespace(&c);
        if ((ret = parse(&c)) == ParseRes::PARSE_OK)
        {
            parse_whitespace(&c);
            if (*c.jsonstr != '\0')
                ret = ParseRes::PARSE_ROOT_NOT_SINGULAR;
        }
        return ret;
    }

    Json::ParseRes Json::parse(ParseContext *c)
    {
        switch (*c->jsonstr)
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
        case '{':
            return parse_object(c);
        case '\0':
            return PARSE_EXPECT_VALUE;
        default:
            return PARSE_INVALID_VALUE;
        };
    }

    Json::ParseRes Json::parse_whitespace(ParseContext *c)
    {
        const char *p = c->jsonstr;
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
            p++;
        c->jsonstr = p;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_null(ParseContext *c)
    {
        if (c->jsonstr[0] != 'n' || c->jsonstr[1] != 'u' || c->jsonstr[2] != 'l' || c->jsonstr[3] != 'l')
            return ParseRes::PARSE_INVALID_VALUE;
        c->jsonstr += 4;
        type = Type::_NULL;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_boolen(ParseContext *c)
    {
        if (c->jsonstr[0] == 't')
        {
            if (c->jsonstr[1] != 'r' || c->jsonstr[2] != 'u' || c->jsonstr[3] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->jsonstr += 4;
            c->buffer.append(std::move(Value(true)));
            this->type = Type::BOOLEN;
            this->val.boolen = true;
        }
        else if (c->jsonstr[0] == 'f')
        {
            if (c->jsonstr[1] != 'a' || c->jsonstr[2] != 'l' || c->jsonstr[3] != 's' || c->jsonstr[4] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->jsonstr += 5;
            c->buffer.append(std::move(Value(false)));
            this->type = Type::BOOLEN;
            this->val.boolen = false;
        }
        else
            return ParseRes::PARSE_INVALID_VALUE;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_string(ParseContext *c)
    {
        const char *p = c->jsonstr;
        p += 1;
        String s(10);
        while (1)
        {
            char ch = *p;
            switch (*p++)
            {
            case '\"':
                c->jsonstr = p;
                c->buffer.append(s);
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
        ParseRes ret;
        Array a;

        c->jsonstr += 1;
        while (1)
        {
            parse_whitespace(c);
            if ((ret = parse(c)) != ParseRes::PARSE_OK)
                return ret;
            parse_whitespace(c);
            switch (*c->jsonstr++)
            {
            case ']':
                c->buffer.append(a);
                this->val = std::move(a);
                this->type = Type::ARRAY;
                return ParseRes::PARSE_OK;
            case ',':
                a.append(c->buffer.pop());
                break;
            case '\0':
                return ParseRes::PARSE_MISS_SQUARE_BRACKET;
            default:
                return ParseRes::PARSE_INVALID_VALUE;
            }
        }
    }

    Json::ParseRes Json::parse_object(ParseContext *c)
    {
        return ParseRes::PARSE_OK;
    }

}
