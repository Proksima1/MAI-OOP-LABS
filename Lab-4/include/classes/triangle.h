#pragma once

#include "figure.h"
#include <memory>

template<Scalar T>
class Triangle : public Figure<T> {
public:
    using Figure<T>::Figure;

    template<Scalar U>
    friend std::istream &operator>>(std::istream &in, Triangle<U> &triangle);

    template<Scalar U>
    friend std::ostream &operator<<(std::ostream &out, const Triangle<U> &triangle);
};

template<Scalar U>
std::istream &operator>>(std::istream &cin, Triangle<U> &triangle) {
    std::cout << "Enter triangle vertices in format <x y\\n>:" << std::endl;

    std::string x, y;
    auto first_point = Point<U>();
    cin >> first_point.x >> first_point.y;

    auto second_point = Point<U>();
    cin >> second_point.x >> second_point.y;

    auto third_point = Point<U>();
    cin >> third_point.x >> third_point.y;
    auto vertices = std::vector<Point<U>>({first_point, second_point, third_point});
    triangle._vertices.swap(vertices);
    return cin;
}

template<Scalar U>
std::ostream &operator<<(std::ostream &out, const Triangle<U> &triangle) {
    out << triangle._vertices;
    return out;
}