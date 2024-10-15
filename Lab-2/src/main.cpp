#include <iostream>
#include "stdlib.h"
#include "classes/binary.h"


int main() {
//    Binary b = Binary(5, '2');
    Binary b1 = Binary("1101");
    Binary b2 = Binary("1010");
//    b2 += b1;
    std::cout << (b2 < b1);
    std::cout << (b1 < b2);


//    delete b;
}