#pragma once

#include "Matrix.h"


class DenseMatrix : public Matrix {
public:
    double get(size_t x, size_t y) const override;

    void set(size_t x, size_t y, double value) override;
};
