#pragma once

#include "Matrix.h"
#include <vector>
#include "DenseMatrix.h"

class SparseRowColumnMatrix : public Matrix {
protected:
    std::vector<double> diagonal;
    std::vector<double> rowLowerProfile;
    std::vector<double> columnUpperProfile;
    std::vector<size_t> indexFirst;
    std::vector<size_t> indexNonZero;
public:
    explicit SparseRowColumnMatrix(const Matrix& matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    std::vector<double> multiply(std::vector<double> &v);

    size_t size() const override;
};
