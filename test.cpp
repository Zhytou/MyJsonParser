#include "AtomJson.hpp"
#include "gtest/gtest.h"

using namespace ajson;

TEST(JsonParse, HandleNull)
{
    Json json;
    EXPECT_EQ(json.parse("null"), AtomJson::Json::ParseRes::PARSE_OK);
}

TEST(JsonParse, HandleBoolen)
{
    Json json;
    EXPECT_EQ(json.parse("true"), Json::ParseRes::PARSE_OK);
    EXPECT_EQ(json.isTrue(), true);
    EXPECT_EQ(json.parse("false"), Json::ParseRes::PARSE_OK);
    EXPECT_EQ(json.isFalse(), true);
}

#define TEST_NUMBER(jsonstr, expected)                            \
    do                                                            \
    {                                                             \
        EXPECT_EQ(json.parse(jsonstr), Json::ParseRes::PARSE_OK); \
        EXPECT_EQ(json.getNumber(), expected);                    \
    } while (0)

TEST(JsonParse, HandleNumber)
{
    Json json;
    TEST_NUMBER("0", 0.0);
    TEST_NUMBER("-0", 0.0);
    TEST_NUMBER("-0.0", 0.0);
    TEST_NUMBER("1", 1);
    TEST_NUMBER("-1", -1);
    TEST_NUMBER("1.5", 1.5);
    TEST_NUMBER("-1.5", -1.5);
    TEST_NUMBER("3.1416", 3.1416);
    TEST_NUMBER("1E10", 1E10);
    TEST_NUMBER("1e10", 1e10);
    TEST_NUMBER("1E+10", 1E+10);
    TEST_NUMBER("1E-10", 1E-10);
    TEST_NUMBER("-1E10", -1E10);
    TEST_NUMBER("-1e10", -1e10);
    TEST_NUMBER("-1E+10", -1E+10);
    TEST_NUMBER("-1E-10", -1E-10);
    TEST_NUMBER("1.234E+10", 1.234E+10);
    TEST_NUMBER("1.234E-10", 1.234E-10);
    TEST_NUMBER("1e-10000", 0.0);
    ;
}

#define TEST_STRING(jsonstr, expected)                            \
    do                                                            \
    {                                                             \
        json.parse(jsonstr);                                      \
        EXPECT_EQ(json.parse(jsonstr), Json::ParseRes::PARSE_OK); \
        String s = json.getString();                              \
        EXPECT_EQ(s == expected, true);                           \
    } while (0)

TEST(JsonParse, HandleString)
{
    Json json;
    TEST_STRING("\"\"", "");
    TEST_STRING("\"this is a string\"", "this is a string");
    TEST_STRING("\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"", "\" \\ / \b \f \n \r \t");
}

#define TEST_ARRAY(jsonstr, expected)                             \
    do                                                            \
    {                                                             \
        EXPECT_EQ(json.parse(jsonstr), Json::ParseRes::PARSE_OK); \
        for (size_t i = 0; i < json.length(); i++)                \
        {                                                         \
            EXPECT_EQ(json[i] == expected[i], true);              \
        }                                                         \
    } while (0)

TEST(JsonParse, HandleArray)
{
    Json json;
    Array a;
    TEST_ARRAY("[]", a);

    a.append(String("hello"));
    a.append(String("world"));
    TEST_ARRAY("[\"hello\",\"world\"]", a);

    Array a1;
    a1.append(true);
    a1.append(false);
    a.append(a1);
    TEST_ARRAY("[\"hello\",\"world\",[true,false]]", a);
}

#define TEST_OBJECT(jsonstr, expected)                                                   \
    do                                                                                   \
    {                                                                                    \
        EXPECT_EQ(json.parse(jsonstr), Json::ParseRes::PARSE_OK);                        \
        Array keys = expected.keys();                                                    \
        for (size_t i = 0; i < keys.length(); i++)                                       \
        {                                                                                \
            EXPECT_EQ(json[keys[i].getString()] == expected[keys[i].getString()], true); \
        }                                                                                \
    } while (0)

TEST(JsonParse, HandleObject)
{
    Json json;
    Object o;

    TEST_OBJECT("{}", o);

    o["first name"] = "Yang";
    TEST_OBJECT("{\"first name\" : \"Yang\"}", o);

    o["last name"] = "Zhong";
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\"}", o);

    o["age"] = 18.0;
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 18}", o);

    o["age"] = 20.5;
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20}", o);

    Object o1;
    o1["last name"] = "Zhong";
    o1["phone number"] = "xxx - xxxx - xxxx";
    o["parent"] = o1;
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20, \"parent\" : {\"last name\" : \"Zhong\", \"phone number\" : \"xxx - xxxx - xxxx\"}}", o);
}
