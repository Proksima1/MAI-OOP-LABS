#pragma once

#include "figure.h"

class Array {
public:
    Array();

    Array(int size);

    virtual ~Array();

    void del(int index);

    void add(int index, Figure *figure);

    int getSize() const { return _size; }

    void callBasicFunctions();

    double total_area();

    Figure *operator[](int index) const;

private:
    Figure **_figures;
    int _size;
};