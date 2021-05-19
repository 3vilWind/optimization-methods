#pragma once

#include "Vector.h"

class SquareMatrix {
public:
    virtual size_t size() const = 0;

    virtual Vector row(size_t index) const = 0;

    virtual Vector mulByVector(const Vector& v) const = 0;

    virtual ~SquareMatrix() = default;

    virtual double getMaxEigenValue() const = 0;
};
