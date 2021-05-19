#pragma once

#include "SquareMatrix.h"


class Matrix : public SquareMatrix {
private:
    std::vector<Vector> matrix;
public:
    explicit Matrix(std::vector<Vector>);

    size_t size() const override;

    Vector row(size_t index) const override;

    Vector mulByVector(const Vector& v) const override;

    double getMaxEigenValue() const override;
};

