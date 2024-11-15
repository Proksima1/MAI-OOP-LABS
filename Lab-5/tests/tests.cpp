#include <gtest/gtest.h>
#include "custom_memory_resources.h"
#include "linked_list.h"

TEST(StackTest, SizeTest) {
    CustomMemoryResource memoryResource;
    auto list = LinkedList<int>(&memoryResource);
    EXPECT_EQ(list.empty(), true);
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(StackTest, ForTest) {
    CustomMemoryResource memoryResource;
    auto list = LinkedList<int>(&memoryResource);
    std::vector<int> v{1, 2, 3};
    for (int i = 0; i < v.size(); ++i) {
        list.push_back(v[i]);
    }
    int i = 0;
    for (auto b: list) {
        EXPECT_EQ(b, v[i]);
        i++;
    }
}

TEST(StackTest, DeleteTest) {
    CustomMemoryResource memoryResource;
    auto list = LinkedList<int>(&memoryResource);
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    for (int i: v) {
        list.push_back(i);
    }
    list.remove(4);
    EXPECT_EQ(list.size(), v.size() - 1);
    v.erase(std::find(v.begin(), v.end(), 4));
    int i = 0;
    for (auto b: list) {
        EXPECT_EQ(b, v[i]);
        i++;
    }

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}