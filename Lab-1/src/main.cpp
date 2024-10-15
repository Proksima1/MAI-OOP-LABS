#include <iostream>
#include "utils.h"


int main() {
    int data;
    std::cin >> data;
    if (checkClear(data)) {
        std::cout << "Clear number" << std::endl;
    } else {
        std::cout << "Unclear number" << std::endl;
    }
    return 1;
}
