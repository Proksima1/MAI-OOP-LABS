#include "classes/array.h"

Array::Array() {
    _size = 5;
    _figures = new Figure *[_size];
    for (int i = 0; i < _size; i++) {
        _figures[i] = nullptr;
    }
}

Array::Array(int size) {
    _size = size;
    _figures = new Figure *[_size];
    for (int i = 0; i < _size; i++) {
        _figures[i] = nullptr;
    }
}

Array::~Array() {
    _size = 0;
    delete[] _figures;
    _figures = nullptr;
}
void validateIndex(int index, int size){
    if (index < 0 || size <= index)
        throw std::invalid_argument("Invalid index");
}

void Array::del(int index) {
    validateIndex(index, _size);
    _figures[index] = nullptr;
}

void Array::add(int index, Figure *figure) {
    validateIndex(index, _size);
    delete _figures[index];
    _figures[index] = figure;
}

double Array::total_area() {
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        if (_figures[i] != nullptr)
            res += (double) *_figures[i];
    }
    return res;
}


Figure *Array::operator[](int index) const {
    validateIndex(index, _size);
    return _figures[index];
}

void Array::callBasicFunctions() {
    for (int i = 0; i < _size; ++i) {
        if (_figures[i] != nullptr) {
            std::cout << "Figure №" << i + 1 << std::endl;
            std::cout << "Center of " << _figures[i]->getCenter() << std::endl;
            std::cout << "Area of figure: " << (double) *_figures[i] << std::endl;
        }
    }
}
