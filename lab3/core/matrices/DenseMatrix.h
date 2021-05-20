#pragma once

#include <vector>
#include "Matrix.h"


class DenseMatrix : public Matrix {
    std::vector<std::vector<double>> matrix;
public:
    explicit DenseMatrix(std::vector<std::vector<double>> matrix);
    double get(size_t x, size_t y) const override;

    void set(size_t x, size_t y, double value) override;
};
