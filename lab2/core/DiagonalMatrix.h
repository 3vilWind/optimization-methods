#pragma once

#include "SquareMatrix.h"

class DiagonalMatrix : public SquareMatrix {
private:
    Vector diagonal;
public:
    explicit DiagonalMatrix(Vector diagonal);

    size_t size() const override;

    Vector row(size_t index) const override;

    Vector mulByVector(const Vector& v) const override;

    double getMaxEigenValue() const override;

    static DiagonalMatrix getRandomMatrix(size_t size, double k);
};