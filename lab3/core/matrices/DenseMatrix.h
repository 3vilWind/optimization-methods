#pragma once

#include <vector>
#include <string>
#include "Matrix.h"
#include "lab2/core/Vector.h"

class DenseMatrix : public Matrix {
    std::vector<std::vector<double>> matrix;
public:
    DenseMatrix() = default;

    explicit DenseMatrix(std::vector<std::vector<double>> matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;

    void swap_rows(size_t row1, size_t row2);

    friend void serialize(const DenseMatrix &matrix, const std::string &path);

    friend void deserialize(DenseMatrix &matrix, const std::string &path);

    static DenseMatrix identityMatrix(size_t size);

    Vector multiply(Vector v);
};
