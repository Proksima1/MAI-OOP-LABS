#pragma once

#include "figure.h"
#include <memory>

struct TriangleVertices : Vertices {
    Point x1;
    Point x2;
    Point x3;
public:
    friend std::ostream &operator<<(std::ostream &out, const TriangleVertices &vertices);

    bool operator==(const TriangleVertices &other) const;
};

class Triangle : public Figure {
public:
    Triangle() = default;

    Triangle(TriangleVertices v);


    Vertices getPos() override;

    friend std::istream &operator>>(std::istream &is, Triangle &triangle);

    friend std::ostream &operator<<(std::ostream &out, const Triangle &triangle);

    Point getCenter() override;

protected:
    double _getArea() const override;


private:
    TriangleVertices _vertices{};
};