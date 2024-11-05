#pragma once

#include "stdlib.h"
#include <iostream>
#include <memory>
#include "point.h"
#include "vector"
#include "exceptions.h"


template<Scalar T>
class Figure {
public:
    Figure();

    Figure(std::initializer_list<Point<T>> list);

    Figure(const Figure &other);

    Figure(Figure &&other) noexcept;

    Point<T> getCenter() const;

    operator double() const {
        return _getArea();
    };

    Figure &operator=(const Figure &other);

    Figure &operator=(Figure &&other) noexcept;

    bool operator==(const Figure &other) const;

    virtual ~Figure() = default;

    template<Scalar U>
    friend std::istream &operator>>(std::istream &is, Figure<U> &figure);

    template<Scalar U>
    friend std::ostream &operator<<(std::ostream &out, const Figure<U> &figure);

protected:
    std::vector<Point<T>> _vertices;

protected:
    double _getArea() const;
};


template<Scalar T>
Figure<T>::Figure() {
    _vertices = std::vector<Point<T>>();
    _vertices.push_back(Point<T>(0, 0));
}

template<Scalar T>
Figure<T>::Figure(const std::initializer_list<Point<T>> t) {
    auto vertices = std::vector<Point<T>>();
    for (Point<T> point: t) {
        vertices.push_back(point);
    }
    _vertices.swap(vertices);
}

template<Scalar T>
Figure<T>::Figure(const Figure &other) {
    _vertices = std::vector(other._vertices);
}

template<Scalar T>
Figure<T>::Figure(Figure &&other) noexcept {
    _vertices = other._vertices;
    other._vertices.clear();
}


template<Scalar T>
Figure<T> &Figure<T>::operator=(const Figure<T> &other) {
    if (this != &other) {
        this->_vertices = other._vertices;
    }
    return *this;
}

template<Scalar T>
Figure<T> &Figure<T>::operator=(Figure<T> &&other) noexcept {
    this->_vertices = other._vertices;
    other._vertices.clear();
    return *this;
}

template<Scalar T>
bool Figure<T>::operator==(const Figure<T> &other) const {
    if (this == &other) {
        return true;
    }
    if (_vertices.size() == other._vertices.size()) {
        for (int i = 0; i < _vertices.size(); ++i) {
            if (other._vertices[i] != _vertices[i])
                return false;
        }
        return true;
    }
    return false;
}

template<Scalar T>
Point<T> Figure<T>::getCenter() const {
    auto result = Point<T>();

    for (int i = 0; i < _vertices.size(); ++i) {
        result.x += _vertices[i].x;
        result.y += _vertices[i].y;
    }
    result.x /= static_cast<double>(_vertices.size());
    result.y /= static_cast<double>(_vertices.size());

    return result;
}

template<Scalar T>
double Figure<T>::_getArea() const {
    T area = static_cast<T>(0);

    for (int i = 0; i < _vertices.size() - 1; ++i)
        area += (_vertices[i].x * (_vertices[i + 1].y - _vertices[i - 1].y));

    area += (_vertices[_vertices.size() - 1].x * (_vertices[0].y - _vertices[_vertices.size() - 2].y));
    area = std::abs(area);
    area /= 2;

    return area;
}

template<Scalar U>
std::ostream &operator<<(std::ostream &out, const Figure<U> &figure) {
    throw NotImplemented("Method not implemented");
}

template<Scalar U>
std::istream &operator>>(std::istream &is, Figure<U> &figure) {
    throw NotImplemented("Method not implemented");
}
