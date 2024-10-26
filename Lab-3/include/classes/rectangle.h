#pragma once

#include "figure.h"
#include <memory>

struct RectangleVertices : Vertices {
    Point x1;
    Point x2;
    Point x3;
    Point x4;
public:
    friend std::ostream &operator<<(std::ostream &out, const RectangleVertices &vertices);

    bool operator==(const RectangleVertices &other) const;

};

class Rectangle : public Figure {
public:
    Rectangle() = default;

    Rectangle(RectangleVertices v);

    Vertices getPos() override;

    friend std::istream &operator>>(std::istream &is, Rectangle &rectangle);

    friend std::ostream &operator<<(std::ostream &out, const Rectangle &rectangle);

    Point getCenter() override;

protected:
    double _getArea() const override;


private:
    RectangleVertices _vertices{};
};