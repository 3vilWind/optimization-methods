#pragma once

#include "Vector.h"

class SquareMatrix {
public:
    virtual size_t number_of_rows() = 0;

    virtual size_t number_of_columns() = 0;

    virtual Vector row(size_t index) = 0;

    virtual Vector vector_multiplication(Vector v) = 0;

    virtual ~SquareMatrix() = default;
};
