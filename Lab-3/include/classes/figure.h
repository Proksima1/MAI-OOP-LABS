#pragma once

#include "stdlib.h"
#include <iostream>
#include <memory>


struct Point {
    double x;
    double y;
public:
    friend std::ostream &operator<<(std::ostream &out, const Point &point);

    bool operator==(const Point &other) const;

};

struct Vertices {
public:
    friend std::ostream &operator<<(std::ostream &out, const Vertices &vertices);

    bool operator==(const Vertices &other) const = default;

};

class Figure {
public:

    virtual Vertices getPos() = 0;

    virtual Point getCenter() = 0;

    operator double() const {
        return _getArea();
    };

    Figure &operator=(const Figure &other);

    Figure &operator=(Figure &&other) noexcept;

    bool operator==(const Figure &other) const;

    virtual ~Figure() = default;

private:
    Vertices _vertices{};

protected:
    virtual double _getArea() const = 0;
};