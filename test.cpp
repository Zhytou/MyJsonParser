// test.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include "gtest/gtest.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}
