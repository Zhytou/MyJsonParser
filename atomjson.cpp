#include "atomjson.h"

namespace AtomJson
{
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
            val.b = true;
        }
        else if (c->json[0] == 'f')
        {
            if (c->json[1] != 'a' || c->json[2] != 'l' || c->json[3] != 's' || c->json[4] != 'e')
                return ParseRes::PARSE_INVALID_VALUE;
            c->json += 5;
            type = AtomJsonType::BOOLEN;
            val.b = false;
        }
        else
            return ParseRes::PARSE_INVALID_VALUE;
        return ParseRes::PARSE_OK;
    }

    Json::ParseRes Json::parse_string(ParseContext *c)
    {
        const char *p = c->json;
        p += 1;
        AtomJsonType::String s;
        while (1)
        {
            char ch = *p;
            switch (*p++)
            {
            case '\"':
                break;
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
                    s.append('\t');
                    break;
                case 't':
                    s.append('\t');
                    break;
                default:
                    return ParseRes::PARSE_INVALID_STRING_ESCAPE;
                }
            }
            case '\0':
                return ParseRes::PARSE_INVALID_STRING_ESCAPE;
            default:
                if ((unsigned char)ch < 0x20)
                    return ParseRes::PARSE_INVALID_STRING_CHAR;
                s.append(ch);
            }
        }
        val.s = std::move(s);
        type = AtomJsonType::Type::STRING;
        return ParseRes::PARSE_OK;
    }

}
