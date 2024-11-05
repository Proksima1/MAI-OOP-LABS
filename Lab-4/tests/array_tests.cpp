#include <gtest/gtest.h>
#include "classes/array.h"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size, 0);
    EXPECT_EQ(arr.getCapacity(), 0);
}

TEST(ArrayTest, ConstructorWithSize) {
    Array<int> arr(5);
    EXPECT_EQ(arr.size, 0);
    EXPECT_EQ(arr.getCapacity(), 5);
}

TEST(ArrayTest, InitializerListConstructor) {
    Array<int> arr = {1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size, 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.size, arr1.size);
    EXPECT_TRUE(arr2 == arr1);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2(std::move(arr1));
    EXPECT_EQ(arr2.size, 3);
    EXPECT_EQ(arr1.size, 0);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    EXPECT_EQ(arr.size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, Remove) {
    Array<int> arr = {1, 2, 3, 4, 5};
    arr.remove(2);
    EXPECT_EQ(arr.size, 4);
    EXPECT_EQ(arr[2], 4);
}

TEST(ArrayTest, EqualityOperator) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2 = {1, 2, 3};
    Array<int> arr3 = {4, 5, 6};
    EXPECT_TRUE(arr1 == arr2);
    EXPECT_FALSE(arr1 == arr3);
}

TEST(ArrayTest, InequalityOperator) {
    Array<int> arr1 = {1, 2, 3};
    Array<int> arr2 = {4, 5, 6};
    EXPECT_TRUE(arr1 != arr2);
}

TEST(ArrayTest, SubscriptOperator) {
    Array<int> arr = {10, 20, 30};
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}