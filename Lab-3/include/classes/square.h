#pragma once

//#include "figure.h"
#include "rectangle.h"
#include <memory>

struct SquareVertices : Vertices {
    Point x1;
    Point x2;
    Point x3;
    Point x4;

public:
    friend std::ostream &operator<<(std::ostream &out, const SquareVertices &vertices);

    bool operator==(const SquareVertices &other) const;

};

class Square : public Rectangle {
public:
    Square() = default;

    Square(SquareVertices v);

    Vertices getPos() override;

    friend std::istream &operator>>(std::istream &is, Square &Square);

    friend std::ostream &operator<<(std::ostream &out, const Square &Square);

    Point getCenter() override;

protected:
    double _getArea() const override;


private:
    SquareVertices _vertices{};
};