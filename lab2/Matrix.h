#pragma once

#include "SquareMatrix.h"


class Matrix : public SquareMatrix {
private:
    std::vector<Vector> matrix;
public:
    explicit Matrix(std::vector<Vector>);

    size_t number_of_rows() override;

    size_t number_of_columns() override;

    Vector row(size_t index) override;

    Vector vector_multiplication(Vector v) override;
};

