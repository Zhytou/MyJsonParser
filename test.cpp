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
