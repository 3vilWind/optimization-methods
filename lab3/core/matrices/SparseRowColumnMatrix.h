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
    explicit SparseRowColumnMatrix(DenseMatrix matrix);

    double get(size_t x, size_t y) const override;

    void set(size_t x, size_t y, double value) override;
};
