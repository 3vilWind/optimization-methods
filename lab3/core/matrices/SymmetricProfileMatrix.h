#pragma once

#include <vector>
#include "Matrix.h"


class SymmetricProfileMatrix : public Matrix {
    std::vector<double> diagonal;
    std::vector<double> rowLowerProfile;
    std::vector<double> columnUpperProfile;
    std::vector<size_t> index;

public:
    double get(size_t x, size_t y) const override;

    void set(size_t x, size_t y, double value) override;
};