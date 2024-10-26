#include "classes/rectangle.h"
#include "math.h"

std::ostream &operator<<(std::ostream &out, const RectangleVertices &vertices) {
    out << "Rectangle vertices:" << std::endl;
    out << vertices.x1 << std::endl;
    out << vertices.x2 << std::endl;
    out << vertices.x3 << std::endl;
    out << vertices.x4 << std::endl;
    return out;
}

bool RectangleVertices::operator==(const RectangleVertices &other) const {
    if (this->x1 == other.x1 && this->x2 == other.x2 && this->x3 == other.x3 && this->x4 == other.x4) {
        return true;
    }
    return false;
}


std::istream &operator>>(std::istream &cin, Rectangle &triangle) {
    std::cout << "Enter rectangle vertices in format <x y\\n>:" << std::endl;
    RectangleVertices *v = new RectangleVertices();
    std::string x, y;
    cin >> x >> y;
    v->x1 = Point{std::stod(x), std::stod(y)};
    cin >> x >> y;
    v->x2 = Point{std::stod(x), std::stod(y)};
    cin >> x >> y;
    v->x3 = Point{std::stod(x), std::stod(y)};
    cin >> x >> y;
    v->x4 = Point{std::stod(x), std::stod(y)};
    triangle._vertices = *v;
    return cin;
}

std::ostream &operator<<(std::ostream &out, const Rectangle &triangle) {
    out << triangle._vertices;
    return out;
}


Vertices Rectangle::getPos() {
    return this->_vertices;
}

double Rectangle::_getArea() const {
    RectangleVertices points = _vertices;

    double a = std::sqrt(
            std::pow(abs(_vertices.x2.x - _vertices.x1.x), 2) + std::pow(abs(_vertices.x2.y - _vertices.x1.y), 2));
    double b = std::sqrt(
            std::pow(_vertices.x3.x - _vertices.x2.x, 2) + std::pow(abs(_vertices.x3.y - _vertices.x2.y), 2));
    return a * b;
}

Point Rectangle::getCenter() {
    double x = (_vertices.x1.x + _vertices.x2.x + _vertices.x3.x + _vertices.x4.x) / 4;
    double y = (_vertices.x1.y + _vertices.x2.y + _vertices.x3.y + _vertices.x4.y) / 4;

    return Point(x, y);
}

Rectangle::Rectangle(RectangleVertices v) {
    this->_vertices = v;
}




