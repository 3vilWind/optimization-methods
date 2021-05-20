#pragma once

#include <stddef.h>


class Matrix {
public:
    virtual double get(size_t x, size_t y) const = 0;

    virtual void set(size_t x, size_t y, double value) = 0;

};
