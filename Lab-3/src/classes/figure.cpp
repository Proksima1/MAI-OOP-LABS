#include "classes/figure.h"

std::ostream &operator<<(std::ostream &out, const Point &point) {
    out << "Point:" << std::endl;
    out << "x: " << point.x << std::endl;
    out << "y: " << point.y;
    return out;
}

bool Point::operator==(const Point &other) const {
    if (this->x == other.x && this->y == other.y){
        return true;
    }
    return false;
}

Figure &Figure::operator=(const Figure &other) {
    if (this != &other) {
        this->_vertices = other._vertices;
    }
    return *this;
}

Figure &Figure::operator=(Figure &&other) noexcept {
    this->_vertices = other._vertices;
    delete &other;
    return *this;
}

bool Figure::operator==(const Figure &other) const {
    if (this == &other){
        return true;
    }
    if (this->_vertices == other._vertices){
        return true;
    }
    return false;
}