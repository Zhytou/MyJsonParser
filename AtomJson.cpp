#include "errno.h"
#include "math.h"
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
            val.obj = v.obj;
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
            val.obj = other.val.obj;
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
            val.obj = std::move(other.val.obj);
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
        this->setNull();
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
            val.obj = other.val.obj;
            break;
        default:
            break;
        }

        return *this;
    }

    Value &Value::operator=(Value &&other)
    {
        this->setNull();
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
            val.obj = std::move(other.val.obj);
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
            val.obj.~Object();
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

    const Value &Value::operator[](size_t idx) const
    {
        assert(isArray());
        return val.arr[idx];
    }

    Value &Value::operator[](const String &key)
    {
        assert(isObject());
        return val.obj[key];
    }

    bool Value::operator==(const Value &other)
    {
        if (type == other.type)
        {
            switch (type)
            {
            case Type::BOOLEN:
                return val.boolen == other.val.boolen;
            case Type::NUMBER:
                return val.num == other.val.num;
            case Type::STRING:
                return val.str == other.val.str;
            case Type::ARRAY:
                return val.arr == other.val.arr;
            case Type::OBJECT:
                return val.obj == other.val.obj;
            default:
                return true;
            }
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &out, const Value &v)
    {
        switch (v.type)
        {
        case Type::BOOLEN:
            if (v.val.boolen)
                out << "true";
            else
                out << "false";
            break;
        case Type::NUMBER:
            out << v.val.num;
            break;
        case Type::STRING:
            out << v.val.str;
            break;
        case Type::ARRAY:
            out << stringify(v, false);
            break;
        case Type::OBJECT:
            out << stringify(v, false);
            break;
        default:
            break;
        }
        return out;
    }

    ParseRes parse_whitespace(ParseContext *c);

    Value parse(const char *jsonstr)
    {
        Value v;
        ParseContext c(jsonstr);
        ParseRes ret;

        parse_whitespace(&c);
        if ((ret = v.parse(&c)) == ParseRes::PARSE_OK)
        {
            parse_whitespace(&c);
            if (*c.jsonstr != '\0')
                ret = ParseRes::PARSE_ROOT_NOT_SINGULAR;
        }
        assert(ret == ParseRes::PARSE_OK);
        return v;
    }

    String stringify(const Value &v, bool prettify, bool scientificNotation, bool customize, size_t customPrecision, bool keepEscape)
    {
        StringifyParam p(prettify, scientificNotation, customize, customPrecision, keepEscape);
        return v.stringify(&p);
    }

    ParseRes Value::parse(ParseContext *c)
    {
        switch (*c->jsonstr)
        {
        case 'n':
            return parse_null(c);
        case 't':
        case 'f':
            return parse_boolen(c);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            return parse_number(c);
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

    ParseRes parse_whitespace(ParseContext *c)
    {
        const char *p = c->jsonstr;
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
            p++;
        c->jsonstr = p;
        return ParseRes::PARSE_OK;
    }

    ParseRes Value::parse_null(ParseContext *c)
    {
        if (c->jsonstr[0] != 'n' || c->jsonstr[1] != 'u' || c->jsonstr[2] != 'l' || c->jsonstr[3] != 'l')
            return ParseRes::PARSE_INVALID_VALUE;
        c->jsonstr += 4;
        type = Type::_NULL;
        return ParseRes::PARSE_OK;
    }

    ParseRes Value::parse_boolen(ParseContext *c)
    {
        if (c->jsonstr[0] == 't')
        {
            if (c->jsonstr[1] != 'r' || c->jsonstr[2] != 'u' || c->jsonstr[3] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->jsonstr += 4;
            this->type = Type::BOOLEN;
            this->val.boolen = true;
        }
        else if (c->jsonstr[0] == 'f')
        {
            if (c->jsonstr[1] != 'a' || c->jsonstr[2] != 'l' || c->jsonstr[3] != 's' || c->jsonstr[4] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->jsonstr += 5;
            this->type = Type::BOOLEN;
            this->val.boolen = false;
        }
        else
            return ParseRes::PARSE_INVALID_VALUE;
        return ParseRes::PARSE_OK;
    }

    ParseRes Value::parse_number(ParseContext *c)
    {
        bool isZeroStart = false, isFloatPoint = false, isScientificNotation = false;
        const char *p = c->jsonstr;

        if (*p == '-')
        {
            p += 1;
        }

        if (*p == '0')
        {
            isZeroStart = true;
            p += 1;
        }

        while ('0' <= *p && *p <= '9')
        {
            if (isZeroStart)
                return ParseRes::PARSE_INVALID_ZERO_START;
            p += 1;
        }

        if (*p == '.')
        {
            isFloatPoint = true;
            p += 1;
        }

        while ('0' <= *p && *p <= '9')
        {
            p += 1;
        }

        if (*p == 'e' || *p == 'E')
        {
            isScientificNotation = true;
            p += 1;
        }

        if (*p == '+' || *p == '-')
        {
            p += 1;
        }

        while ('0' <= *p && *p <= '9')
        {
            if (!isScientificNotation)
                return ParseRes::PARSE_INVALID_SCIENTIFIC_NOTATION;
            p += 1;
        }

        errno = 0;
        long l;
        double d;
        if (isFloatPoint)
            d = strtod(c->jsonstr, NULL);

        else
            l = strtol(c->jsonstr, NULL, 10);

        if (errno == ERANGE && (d == HUGE_VAL || d == -HUGE_VAL))
            return ParseRes::PARSE_NUMBER_OVERFLOW;

        c->jsonstr = p;
        this->type = Type::NUMBER;
        if (isFloatPoint)
            this->val.num = d;
        else
            this->val.num = l;
        return ParseRes::PARSE_OK;
    }

    ParseRes Value::parse_string(ParseContext *c)
    {
        const char *p = c->jsonstr;
        String s;

        p += 1;
        while (1)
        {
            char ch = *p;
            switch (*p++)
            {
            case '\"':
                c->jsonstr = p;
                this->val.str = std::move(s);
                this->type = Type::STRING;
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
                    return ParseRes::PARSE_STRING_INVALID_STRING_ESCAPE;
                }
                break;
            }
            case '\0':
                return ParseRes::PARSE_STRING_MISS_QUOTATION_MARK;
            default:
                if ((unsigned char)ch < 0x20)
                {
                    return ParseRes::PARSE_STRING_INVALID_STRING_CHAR;
                }
                s.append(ch);
            }
        }
    }

    ParseRes Value::parse_array(ParseContext *c)
    {
        ParseRes ret;
        Array arr;

        // avoid the cases like this [ element , ] or [ , ]
        bool elementPush = false;

        c->jsonstr += 1;
        while (1)
        {
            parse_whitespace(c);
            switch (*c->jsonstr++)
            {
            case ']':
                // avoid the cases like this [ element , ] and allow [ ]
                if (!arr.empty() && !elementPush)
                    return ParseRes::PARSE_ARRAY_INVALID_COMMA;

                this->val = std::move(arr);
                this->type = Type::ARRAY;
                return ParseRes::PARSE_OK;
            case ',':
                // avoid the cases like this [ , element ]
                if (!elementPush)
                    return ParseRes::PARSE_ARRAY_INVALID_COMMA;
                elementPush = false;
                break;
            case '\0':
                return ParseRes::PARSE_ARRAY_MISS_SQUARE_BRACKET;
            default:
                // c->jsonstr -= 1 is to make the jsonstr stay at 'n' or 't' or 'f' or '0 - 9' or '\"' or '[' or '{'
                c->jsonstr -= 1;
                Value element;
                if ((ret = element.parse(c)) != ParseRes::PARSE_OK)
                    return ret;
                arr.append(std::move(element));
                elementPush = true;
            }
        }
    }

    ParseRes Value::parse_object(ParseContext *c)
    {
        ParseRes ret;
        Object obj;

        Value key, value;
        // avoid the cases like this { item , } or { , }
        bool itemPushed = false;

        c->jsonstr += 1;
        while (1)
        {
            parse_whitespace(c);
            switch (*c->jsonstr)
            {
            case '\0':
                return ParseRes::PARSE_OBJECT_MISS_BRACKET;
            case '}':
                c->jsonstr += 1;

                // avoid the cases like this { item , }
                if (!itemPushed && !obj.empty())
                    return ParseRes::PARSE_OBJECT_INVALID_COMMA;

                this->val = std::move(obj);
                this->type = Type::OBJECT;
                return ParseRes::PARSE_OK;
            case '\"':
                if ((ret = key.parse_string(c)) != ParseRes::PARSE_OK)
                    return ret;

                parse_whitespace(c);
                if (*c->jsonstr != ':')
                    return ParseRes::PARSE_OBJECT_MISS_COLON;
                c->jsonstr += 1;

                parse_whitespace(c);
                if ((ret = value.parse(c)) != ParseRes::PARSE_OK)
                    return ret;
                obj[key.getString()] = std::move(value);
                itemPushed = true;
                break;
            case ',':
                // avoid the cases like this { , }
                if (!itemPushed)
                    return ParseRes::PARSE_OBJECT_INVALID_COMMA;
                c->jsonstr += 1;
                break;
            default:
                return ParseRes::PARSE_OBJECT_INVALID_VALUE;
            }
        }
    }

    String Value::stringify(StringifyParam *p) const
    {
        switch (this->type)
        {
        case Type::BOOLEN:
            return stringify_boolen(p);
        case Type::NUMBER:
            return stringify_number(p);
        case Type::STRING:
            return stringify_string(p);
        case Type::ARRAY:
            return stringify_array(p);
        case Type::OBJECT:
            return stringify_object(p);
        default:
            return stringify_null(p);
        }
    }

    String Value::stringify_null(StringifyParam *p) const
    {
        assert(this->type == Type::_NULL);
        String n;
        if (p->prettify)
        {
            for (size_t i = 0; i < p->indentation; i++)
                n.append('\t');
        }
        n.append("null", 0, 4);
        return std::move(n);
    }

    String Value::stringify_boolen(StringifyParam *p) const
    {
        assert(this->type == Type::BOOLEN);
        String b;
        if (p->prettify)
        {
            for (size_t i = 0; i < p->indentation; i++)
                b.append('\t');
        }
        if (this->isTrue())
            b.append("true", 0, 4);
        else
            b.append("false", 0, 5);
        return std::move(b);
    }

    String Value::stringify_number(StringifyParam *p) const
    {
        assert(this->type == Type::NUMBER);
        String n;
        if (p->prettify)
        {
            for (size_t i = 0; i < p->indentation; i++)
                n.append('\t');
        }

        n += this->val.num.to_str(p->scientificNotation, p->customize, p->customPrecision);
        return std::move(n);
    }

    String Value::stringify_string(StringifyParam *p) const
    {
        assert(this->type == Type::STRING);
        String s;
        if (p->prettify)
        {
            s.append('\n');
            for (size_t i = 0; i < p->indentation; i++)
                s.append('\t');
        }

        s.append('\"');
        if (p->keepEscape)
        {
            for (size_t i = 0; i < this->val.str.length(); i++)
            {
                char ch = this->val.str[i];
                switch (ch)
                {
                case '\\':
                    s.append('\\');
                    s.append('\\');
                    break;
                case '/':
                    s.append('\\');
                    s.append('/');
                    break;
                case '\b':
                    s.append('\\');
                    s.append('b');
                    break;
                case '\f':
                    s.append('\\');
                    s.append('f');
                    break;
                case '\n':
                    s.append('\\');
                    s.append('n');
                    break;
                case '\r':
                    s.append('\\');
                    s.append('r');
                    break;
                case '\t':
                    s.append('\\');
                    s.append('t');
                    break;
                default:
                    s.append(ch);
                    break;
                }
            }
        }
        else
        {
            if (this->val.str.length() >= 1)
                s.append(this->val.str, 0, this->val.str.length());
        }
        s.append('\"');

        return std::move(s);
    }

    String Value::stringify_array(StringifyParam *p) const
    {
        assert(this->type == Type::ARRAY);
        String a;

        if (p->prettify)
        {
            a.append('\n');
            for (size_t i = 0; i < p->indentation; i++)
                a.append('\t');
            p->indentation += 1;
        }
        a.append('[');

        for (size_t i = 0; i < this->val.arr.length(); i++)
        {
            if (p->prettify)
                a.append('\n');
            String element = std::move(this->val.arr[i].stringify(p));
            a.append(element, 0, element.length());
            if (i != this->val.arr.length() - 1)
                a.append(',');
        }

        if (p->prettify)
        {
            a.append('\n');
            p->indentation -= 1;
            for (size_t i = 0; i < p->indentation; i++)
                a.append('\t');
        }
        a.append(']');

        return std::move(a);
    }

    String Value::stringify_object(StringifyParam *p) const
    {
        assert(this->type == Type::OBJECT);
        String o;
        if (p->prettify)
        {
            o.append('\n');
            for (size_t i = 0; i < p->indentation; i++)
                o.append('\t');
            p->indentation += 1;
        }
        o.append('{');

        Array keys = std::move(this->val.obj.keys());
        for (size_t i = 0; i < keys.length(); i++)
        {
            String key = std::move(keys[i].stringify(p));
            o.append(key, 0, key.length());
            // must use this getString func to reget the key in order to avoid '\t' or '\n' are added in the front;
            key = keys[i].getString();
            o.append(':');
            if (this->val.obj[key].type != Type::ARRAY && this->val.obj[key].type != Type::OBJECT)
            {
                bool tmp = p->prettify;
                p->prettify = false;
                String value = std::move(this->val.obj[key].stringify(p));
                o.append(value, 0, value.length());
                p->prettify = tmp;
            }
            else
            {
                p->indentation += 1;
                String value = std::move(this->val.obj[key].stringify(p));
                o.append(value, 0, value.length());
                p->indentation -= 1;
            }

            if (i != keys.length() - 1)
                o.append(',');
        }

        if (p->prettify)
        {
            o.append('\n');
            p->indentation -= 1;
            for (size_t i = 0; i < p->indentation; i++)
                o.append('\t');
        }
        o.append('}');

        return std::move(o);
    }
}
