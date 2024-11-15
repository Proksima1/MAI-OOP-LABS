#include <iostream>
#include <linked_list.h>
#include "custom_memory_resources.h"


struct Point {
    int x;
    int y;

    bool operator==(const Point &other) const {
        if ((this->x == other.x) && (this->y == other.y)) {
            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &out, const Point &point) {
        out << "Point(x=" << point.x << ", y=" << point.y << ")";
        return out;
    }

};



int main() {
    CustomMemoryResource memoryResource1;
    auto list1 = LinkedList<int>(&memoryResource1);


    CustomMemoryResource memoryResource2;
    auto list2 = LinkedList<Point>(&memoryResource2);

    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    list1.push_front(40);
    std::cout << list1 << std::endl;

    list1.remove(20);
    std::cout << list1 << std::endl;

    list1.remove(40);
    std::cout << list1 << std::endl;


    list2.push_back({1, 2});
    list2.push_back({3, 4});
    list2.push_back({5, 6});

    list2.push_front({7, 8});

    std::cout << list2 << std::endl;

    list2.remove({3, 4});
    std::cout << list2 << std::endl;


    list2.remove({1, 2});
    std::cout << list2 << std::endl;


    return 0;
}