#pragma once

#include <vector>
#include "Matrix.h"


class DenseMatrix : public Matrix {
    std::vector<std::vector<double>> matrix;
public:
    explicit DenseMatrix(std::vector<std::vector<double>> matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;

    void swap_rows(size_t row1, size_t row2);
};
