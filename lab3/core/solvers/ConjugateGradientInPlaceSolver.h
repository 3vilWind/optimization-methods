#pragma once

#include "Solver.h"

using Vector =std::vector<double>;//а чтоб и нет

class ConjugateGradientInPlaceSolver : public Solver {
    Vector solve(Matrix &a, Vector b) override;

    Vector static subtract(Vector a, Vector &b);

    Vector static sum(Vector a, Vector &b);

    Vector static multiply(Vector v, double x);

    double static scalar_product(Vector &a, Vector &b);
};
