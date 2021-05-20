#pragma once

#include "Matrix.h"


class LWrapperMatrix: public Matrix {
protected:
    const Matrix& matrix;
public:
    explicit LWrapperMatrix(const Matrix& matrix): matrix(matrix) {}

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;
};


class UWrapperMatrix: public Matrix {
protected:
    const Matrix& matrix;
public:
    explicit UWrapperMatrix(const Matrix& matrix): matrix(matrix) {}

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;
};
