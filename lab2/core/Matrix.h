#pragma once

#include "SquareMatrix.h"


class Matrix : public SquareMatrix {
private:
    std::vector<Vector> matrix;
public:
    explicit Matrix(std::vector<Vector>);

    size_t number_of_rows() const override;

    size_t number_of_columns() const override;

    Vector row(size_t index) const override;

    Vector vector_multiplication(const Vector& v) const override;
};

