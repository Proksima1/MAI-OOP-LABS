#include <gtest/gtest.h>
#include "classes/binary.h"

TEST(Lab2, defaultConstructor) {
    Binary b = Binary();
    EXPECT_EQ(b.getSize(), 0);
}


TEST(Lab2, sizeAndDefaultConstructor) {
    Binary b = Binary(4, '1');
    EXPECT_EQ(b.getSize(), 4);
    for (int i = 0; i < b.getSize(); ++i) {
        EXPECT_EQ(b.getData()[i], '1');
    }
}

TEST(Lab2, initializerListConstructor) {
    std::initializer_list<unsigned char> list = {'1', '0', '1', '0', '0'};
    Binary b = Binary(list);
    EXPECT_EQ(b.getSize(), list.size());
    int pos = 0;
    for (unsigned char c: list) {
        EXPECT_EQ(b.getData()[++pos], c);
    }
}

TEST(Lab2, stringConstructor) {
    std::string list = "1010101";
    Binary b = Binary(list);
    EXPECT_EQ(b.getSize(), list.size());
    for (int i = 0; i < b.getSize(); ++i) {
        EXPECT_EQ(b.getData()[i], list[i]);
    }
}


TEST(Lab2, assignOperator) {
    Binary b = Binary();
    Binary b2 = Binary("1010101");
    b = b2;
    EXPECT_EQ(b.getSize(), b2.getSize());
    for (int i = 0; i < b.getSize(); ++i) {
        EXPECT_EQ(b.getData()[i], b2.getData()[i]);
    }
}

TEST(Lab2, additionOperator) {
    Binary b = Binary("1011");
    Binary b2 = Binary("101");
    b += b2;
    std::string expected = "10000";
    EXPECT_EQ(b.getSize(), expected.size());
    for (int i = 0; i < b.getSize(); ++i) {
        EXPECT_EQ(b.getData()[i], expected[i]);
    }
}

TEST(Lab2, substractionOperator) {
    Binary b = Binary("1011");
    Binary b2 = Binary("101");
    b -= b2;
    std::string expected = "0110";
    EXPECT_EQ(b.getSize(), expected.size());
    for (int i = 0; i < b.getSize(); ++i) {
        EXPECT_EQ(b.getData()[i], expected[i]);
    }
}

TEST(Lab2, EqualityOperator)
{

    Binary b1("100010");
    Binary b2("1101");
    Binary b3("100010");

    EXPECT_TRUE(b1 == b3);
    EXPECT_FALSE(b1 == b2);
}

TEST(Lab2, LessThanOperator)
{

    Binary b1("1010");
    Binary b2("1101");

    EXPECT_TRUE(b1 < b2);
    EXPECT_FALSE(b2 < b1);
}

TEST(Lab2, GreaterThanOperator)
{

    Binary b1("1101");
    Binary b2("1000");

    EXPECT_TRUE(b1 > b2);
    EXPECT_FALSE(b2 > b1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}