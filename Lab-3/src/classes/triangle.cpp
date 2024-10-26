#include "classes/triangle.h"
#include "math.h"

std::ostream &operator<<(std::ostream &out, const TriangleVertices &vertices) {
    out << "Triangle vertices:" << std::endl;
    out << vertices.x1 << std::endl;
    out << vertices.x2 << std::endl;
    out << vertices.x3 << std::endl;
    return out;
}

bool TriangleVertices::operator==(const TriangleVertices &other) const {
    if (this->x1 == other.x1 && this->x2 == other.x2 && this->x3 == other.x3) {
        return true;
    }
    return false;
}


std::istream &operator>>(std::istream &cin, Triangle &triangle) {
    std::cout << "Enter triangles vertices in format <x y\\n>:" << std::endl;
    TriangleVertices *v = new TriangleVertices();
    std::string x, y;
    cin >> x >> y;
    v->x1 = Point{std::stod(x), std::stod(y)};
    cin >> x >> y;
    v->x2 = Point{std::stod(x), std::stod(y)};
    cin >> x >> y;
    v->x3 = Point{std::stod(x), std::stod(y)};
    triangle._vertices = *v;
    return cin;
}

std::ostream &operator<<(std::ostream &out, const Triangle &triangle) {
    out << triangle._vertices;
    return out;
}


Vertices Triangle::getPos() {
    return this->_vertices;
}

double Triangle::_getArea() const {
    TriangleVertices points = _vertices;

    return 0.5 * abs(((points.x1.x - points.x3.x) * (points.x2.y - points.x3.y) -
                      (points.x2.x - points.x3.x) * (points.x1.y - points.x3.y)));
}

Point Triangle::getCenter() {
    double x = (_vertices.x1.x + _vertices.x2.x + _vertices.x3.x) / 3;
    double y = (_vertices.x1.y + _vertices.x2.y + _vertices.x3.y) / 3;

    return Point(x, y);
}

Triangle::Triangle(TriangleVertices v) {
    this->_vertices = v;
}


