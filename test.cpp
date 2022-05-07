#include "atomjson.h"
#include "gtest/gtest.h"

TEST(JsonParse, HandleNull)
{
    AtomJson::Json json;
    char jsonstr[] = "null";
    EXPECT_EQ(json.parse(jsonstr), AtomJson::Json::ParseRes::PARSE_OK);
    EXPECT_EQ(json.isEmpty(), true);
}

TEST(JsonParse, HandleBoolen)
{
    AtomJson::Json json;
    char jsonstr1[] = "true";
    EXPECT_EQ(json.parse(jsonstr1), AtomJson::Json::ParseRes::PARSE_OK);
    EXPECT_EQ(json.isBoolen(), true);
}
