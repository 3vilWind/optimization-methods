#pragma once
#include <vector>
#include "lab2/core/Vector.h"
#include "lab3/core/matrices/DenseMatrix.h"

class ScalarFunction {
public:
    virtual double compute(const Vector& x) const = 0;
    virtual Vector gradient(const Vector& x) const = 0;
    virtual DenseMatrix hessian(const Vector& x) const = 0;
    virtual ~ScalarFunction() = default;
};
