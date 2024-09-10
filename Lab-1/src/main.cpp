#include <iostream>
#include "../include/main.h"


int main() {
    int data;
    std::cin >> data;
    if (checkClear(data)) {
        std::cout << "Clear number";
    } else {
        std::cout << "Unclear number";
    }
    return 1;
}
