#pragma once

#include "Vector.h"

class SquareMatrix {
public:
    virtual size_t number_of_rows() const = 0;

    virtual size_t number_of_columns() const = 0;

    virtual Vector row(size_t index) const = 0;

    virtual Vector vector_multiplication(const Vector& v) const = 0;

    virtual ~SquareMatrix() = default;
};
