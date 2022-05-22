﻿#include "AtomJson.hpp"
#include "gtest/gtest.h"

using namespace ajson;

TEST(JsonParse, HandleNull)
{
    Json json = parse("null");
    EXPECT_EQ(json.isNull(), true);
}

TEST(JsonParse, HandleBoolen)
{
    Json json = parse("true");
    EXPECT_EQ(json.isTrue(), true);

    json = parse("false");
    EXPECT_EQ(json.isFalse(), true);
}

#define TEST_NUMBER(jsonstr, expected)         \
    do                                         \
    {                                          \
        json = parse(jsonstr);                 \
        EXPECT_EQ(json.getNumber(), expected); \
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

#define TEST_STRING(jsonstr, expected)  \
    do                                  \
    {                                   \
        json = parse(jsonstr);          \
        String s = json.getString();    \
        EXPECT_EQ(s == expected, true); \
    } while (0)

TEST(JsonParse, HandleString)
{
    Json json;
    TEST_STRING("\"\"", "");
    TEST_STRING("\"this is a string\"", "this is a string");
    TEST_STRING("\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"", "\" \\ / \b \f \n \r \t");
}

#define TEST_ARRAY(jsonstr, expected)                \
    do                                               \
    {                                                \
        json = parse(jsonstr);                       \
        for (size_t i = 0; i < json.length(); i++)   \
        {                                            \
            EXPECT_EQ(json[i] == expected[i], true); \
        }                                            \
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
    a1.append(1);
    a1.append(2);
    a.append(a1);
    TEST_ARRAY("[\"hello\",\"world\",[1,2]]", a);
}

#define TEST_OBJECT(jsonstr, expected)                   \
    do                                                   \
    {                                                    \
        json = parse(jsonstr);                           \
        Array keys = expected.keys();                    \
        for (size_t i = 0; i < keys.length(); i++)       \
        {                                                \
            String key = keys[i].getString();            \
            EXPECT_EQ(json.exist(key), true);            \
            EXPECT_EQ(json[key] == expected[key], true); \
        }                                                \
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
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20.5}", o);

    Object o1;
    o1["last name"] = "Zhong";
    o1["phone number"] = "xxx - xxxx - xxxx";
    o["parent"] = o1;
    TEST_OBJECT("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20.5, \"parent\" : {\"last name\" : \"Zhong\", \"phone number\" : \"xxx - xxxx - xxxx\"}}", o);
}

TEST(JsonStringify, HandleNull)
{
    Json json = parse("null");
    EXPECT_EQ(json.isNull(), true);
    EXPECT_EQ(stringify(json, false), "null");
}

TEST(JsonStringify, HandleBoolen)
{
    Json json;

    json = parse("true");
    EXPECT_EQ(json.isTrue(), true);
    EXPECT_EQ(stringify(json, false), "true");

    json = parse("false");
    EXPECT_EQ(json.isFalse(), true);
    EXPECT_EQ(stringify(json, false), "false");
}

TEST(JsonStringify, HandleNumber)
{
}

TEST(JsonStringify, HandleString)
{
}

TEST(JsonStringify, HandleArray)
{
}

TEST(JsonStringify, HandleObject)
{
}