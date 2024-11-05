#pragma once

#include "iostream"

template<class T>
concept Scalar = std::is_scalar_v<T>;


template<Scalar T>
class Point {
public:
    T x, y;
public:
    Point();

    Point(T x, T y);

    Point(const Point &other);

    Point(Point &&other) noexcept;

    Point &operator=(const Point &other);

    Point &operator=(Point &&other) noexcept;

    template<Scalar U>
    friend std::ostream &operator<<(std::ostream &out, const Point<U> &point);

    bool operator==(const Point &other) const;

};


template<Scalar T>
Point<T>::Point() {
    x = 0;
    y = 0;
}

template<Scalar T>
Point<T>::Point(T x, T y) {
    this->x = x;
    this->y = y;
}

template<Scalar U>
std::ostream &operator<<(std::ostream &out, const Point<U> &point) {
    out << "Point(x:" << point.x << ", y: " << point.y << ")";
    return out;
}

template<Scalar T>
bool Point<T>::operator==(const Point<T> &other) const {
    if (this->x == other.x && this->y == other.y) {
        return true;
    }
    return false;
}

template<Scalar T>
Point<T> &Point<T>::operator=(const Point &other) = default;

template<Scalar T>
Point<T> &Point<T>::operator=(Point &&other) noexcept = default;

template<Scalar T>
Point<T>::Point(const Point &other) {
    this->x = other.x;
    this->y = other.y;
}

template<Scalar T>
Point<T>::Point(Point &&other) noexcept {
    this->x = other.x;
    this->y = other.y;
}
