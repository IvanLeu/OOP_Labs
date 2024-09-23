#include <gtest/gtest.h>
#include <utils.hpp>

TEST(LabTests, random_test) {
	EXPECT_EQ(extract_digits("123abc456dsa7890"), "1234567890");
}

TEST(LabTests, random_test_vol2) {
	EXPECT_EQ(extract_digits("ddsdsajh3214543jdsajdkas321sjsdas22319"), "321454332122319");
}

TEST(LabTests, no_digits_test) {
	EXPECT_EQ(extract_digits("abcdefg"), "");
}

TEST(LabTests, only_digits_test) {
	EXPECT_EQ(extract_digits("1234567890"), "1234567890");
}
