#pragma once

#include "SquareMatrix.h"

class DiagonalMatrix : public SquareMatrix {
private:
    Vector diagonal;
public:
    DiagonalMatrix(size_t size, double k);

    explicit DiagonalMatrix(Vector diagonal);

    size_t number_of_rows() override;

    size_t number_of_columns() override;

    Vector row(size_t index) override;

    Vector vector_multiplication(Vector v) override;
};