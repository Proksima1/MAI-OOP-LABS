#include "classes/square.h"
#include "math.h"

std::ostream &operator<<(std::ostream &out, const SquareVertices &vertices) {
    out << "Square vertices:" << std::endl;
    out << vertices.x1 << std::endl;
    out << vertices.x2 << std::endl;
    out << vertices.x3 << std::endl;
    out << vertices.x4 << std::endl;
    return out;
}

bool SquareVertices::operator==(const SquareVertices &other) const {
    if (this->x1 == other.x1 && this->x2 == other.x2 && this->x3 == other.x3 && this->x4 == other.x4) {
        return true;
    }
    return false;
}


std::istream &operator>>(std::istream &cin, Square &square) {
    SquareVertices *v = new SquareVertices();
    std::cout << "Enter square vertices in format <x y\\n>:" << std::endl;
    std::cout << "Enter up left vertice: ";
    std::string x, y;
    cin >> x >> y;
    v->x1 = Point{std::stod(x), std::stod(y)};
    std::cout << "Enter right down vertice: ";
    cin >> x >> y;
    v->x3 = Point{std::stod(x), std::stod(y)};
    v->x2 = Point{v->x3.x, v->x1.y};
    v->x4 = Point{v->x1.x, v->x3.y};
    square._vertices = *v;
    return cin;
}

std::ostream &operator<<(std::ostream &out, const Square &square) {
    out << square._vertices;
    return out;
}


Vertices Square::getPos() {
    return this->_vertices;
}

double Square::_getArea() const {
    SquareVertices points = _vertices;

    double a = std::sqrt(
            std::pow(abs(_vertices.x2.x - _vertices.x1.x), 2) + std::pow(abs(_vertices.x2.y - _vertices.x1.y), 2));
    double b = std::sqrt(
            std::pow(_vertices.x3.x - _vertices.x2.x, 2) + std::pow(abs(_vertices.x3.y - _vertices.x2.y), 2));
    return a * b;
}

Point Square::getCenter() {
    double x = (_vertices.x1.x + _vertices.x2.x + _vertices.x3.x + _vertices.x4.x) / 4;
    double y = (_vertices.x1.y + _vertices.x2.y + _vertices.x3.y + _vertices.x4.y) / 4;

    return Point(x, y);
}

Square::Square(SquareVertices v) {
    this->_vertices = v;
}




