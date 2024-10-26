#include <iostream>
#include "stdlib.h"
#include "classes/triangle.h"
#include "classes/rectangle.h"
#include "classes/array.h"
#include "classes/square.h"

Figure *get_figure() {
    int number = 0;
    std::cout << "Select figure you want to create:\nTriangle - 1\nRectangle - 2\nSquare - 3" << std::endl;
    std::cout << "Your input: ";
    std::cin >> number;
    switch (number) {
        case 1: {
            Triangle *triangle = new Triangle();
            std::cin >> *triangle;
            return triangle;
        }
        case 2: {
            Rectangle *rectangle = new Rectangle();
            std::cin >> *rectangle;
            return rectangle;
        }
        case 3: {
            Square *square = new Square();
            std::cin >> *square;
            return square;
        }
        default:
            std::cout << "Unknown figure number";
    }
    return nullptr;
}

int call_function(int number, Array *array) {
    switch (number) {
        case 1:
        {
            int index;
            if (array->getSize() == 0) {
                std::cout << "You have zero-length array" << std::endl;
                break;
            }
            std::cout << "Enter position in array to insert figure(starts from 0 till "
                      << array->getSize() - 1 << "): ";
            std::cin >> index;
            Figure *figure = get_figure();

            if (figure != nullptr) {
                array->add(index, figure);
            }
            break;
        }
        case 2:
            std::cout << "Getting center and area for every figure:" << std::endl;
            array->callBasicFunctions();
            break;
        case 3:
            std::cout << "Total area of all figures is: " << array->total_area() << std::endl;
            break;
        case 4:
            int index;
            std::cout << "Enter position in array to delete figure(starts from 0): ";
            std::cin >> index;
            try {
                array->del(index);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        case 5:
            return 0;
    }
    return 1;
}

int main() {
    int size;
    std::cout << "Enter size of figures array: ";
    std::cin >> size;
    Array *array = new Array(size);
    int number, status = 1;
    while (status) {
        std::cout
                << "Menu:\nNew figure - 1\nCall basic functions - 2\nCalculate total area - 3\nDelete figure by index - 4\nExit - 5"
                << std::endl;
        std::cout << "Enter command number: ";
        std::cin >> number;
        status = call_function(number, array);
    }
    delete array;
}