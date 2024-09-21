#include <gtest/gtest.h>
#include "../include/main.h"

TEST(test_clear_number, basic_test_set) {
    int data = 123;
    bool result = checkClear(data);
    ASSERT_TRUE(result);
}

TEST(test_unclear_number, basic_test_set) {
    int data = 132;
    bool result = !checkClear(data);
    ASSERT_TRUE(result);
}

TEST(test_clear_number_with_equal_digits, basic_test_set) {
    int data = 133;
    bool result = checkClear(data);
    ASSERT_TRUE(result);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}