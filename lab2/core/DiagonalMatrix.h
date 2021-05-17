#pragma once

#include "SquareMatrix.h"

class DiagonalMatrix : public SquareMatrix {
private:
    Vector diagonal;
public:
    DiagonalMatrix(size_t size, double k);

    explicit DiagonalMatrix(Vector diagonal);

    size_t number_of_rows() const override;

    size_t number_of_columns() const override;

    Vector row(size_t index) const override;

    Vector vector_multiplication(const Vector& v) const override;
};