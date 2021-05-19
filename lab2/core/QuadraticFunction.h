#pragma once

#include "include/jacobi_pd.hpp"
#include "SquareMatrix.h"
#include "Vector.h"


class QuadraticFunction {
public:
    const SquareMatrix *a;
    const Vector *b;
    const double c;
    const double maxEigenValue;

    QuadraticFunction(const SquareMatrix *a, const Vector *b, double c) : a(a), b(b), c(c),
                                                                          maxEigenValue(a->getMaxEigenValue()) {
    }

    double evaluate(const Vector &x) const {
        return 0.5f * a->mulByVector(x) * x + (*b) * x + c;
    }

    Vector gradient(const Vector &x) const {
        return a->mulByVector(x) + (*b);
    }
};
