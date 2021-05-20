#pragma once

#include "Matrix.h"
#include <vector>
#include "DenseMatrix.h"

class SparseRowColumnMatrix : public Matrix {
private:
    std::vector<double> diagonal;
    std::vector<double> rowLowerProfile;
    std::vector<double> columnUpperProfile;
    std::vector<size_t> indexFirst;
    std::vector<size_t> indexNonZero;
public:
    explicit SparseRowColumnMatrix(const Matrix& matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;
};
