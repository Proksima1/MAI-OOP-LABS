#pragma once

#include "figure.h"
#include <memory>

template<Scalar T>
class Square : public Figure<T> {
public:
    using Figure<T>::Figure;

    template<Scalar U>
    friend std::istream &operator>>(std::istream &in, Square<U> &rectangle);

    template<Scalar U>
    friend std::ostream &operator<<(std::ostream &out, const Square<U> &rectangle);
};

template<Scalar U>
std::istream &operator>>(std::istream &cin, Square<U> &square) {
    std::cout << "Enter square vertices in format <x y\\n>:" << std::endl;
    std::string x, y;
    auto first_point = Point<U>();
    cin >> first_point.x >> first_point.y;

    auto second_point = Point<U>();
    cin >> second_point.x >> second_point.y;

    auto third_point = Point<U>();
    cin >> third_point.x >> third_point.y;
    auto forth_point = Point<U>();
    cin >> forth_point.x >> forth_point.y;
    auto vertices = std::vector<Point<U>>({first_point, second_point, third_point, forth_point});
    square._vertices.swap(vertices);
    return cin;
}

template<Scalar U>
std::ostream &operator<<(std::ostream &out, const Square<U> &square) {
    out << square._vertices;
    return out;
}