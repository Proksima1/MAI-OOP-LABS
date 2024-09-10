#include <gtest/gtest.h>
#include "../include/main.h"

TEST(test_clear_number, basic_test_set) {
    ASSERT_TRUE(checkClear(123) == true);
}

TEST(test_unclear_number, basic_test_set) {
    ASSERT_TRUE(checkClear(132) == false);
}

TEST(test_clear_number_with_equal_digits, basic_test_set) {
    ASSERT_TRUE(checkClear(133) == false);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}