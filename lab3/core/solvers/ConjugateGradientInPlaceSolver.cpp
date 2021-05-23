#include "ConjugateGradientInPlaceSolver.h"
#include "../matrices/SparseRowColumnMatrix.h"
#include <vector>
#include <math.h>
#include <iostream>

Vector ConjugateGradientInPlaceSolver::solve(Matrix &a, Vector b) {
    if (typeid(a) != typeid(SparseRowColumnMatrix)) {
        throw std::runtime_error("Only Sparse Matrices are supported!");
    }
    auto &matrix = dynamic_cast<SparseRowColumnMatrix &>(a);
    Vector x_prev(a.size(), 0);
    x_prev[0] = 1;
    Vector mx = matrix.multiply(x_prev);
    Vector r_prev = subtract(b, mx);
    Vector z_prev = r_prev;
    double eps = 1e-7;
    for (size_t i = 1; i < 1e4; ++i) {
        Vector mz = matrix.multiply(z_prev);
        double alpha = scalar_product(r_prev, r_prev) / scalar_product(mz, z_prev);
        Vector x_cur = sum(multiply(z_prev, alpha), x_prev);
        Vector mz_alpha = multiply(mz, alpha);
        Vector r_cur = subtract(r_prev, mz_alpha);
        double beta = scalar_product(r_cur, r_cur) / scalar_product(r_prev, r_prev);
        Vector z_cur = sum(multiply(z_prev, beta), r_cur);
        if (scalar_product(r_cur, r_cur) / scalar_product(b, b) < eps * eps) {
            return x_cur;
        }
        x_prev = x_cur;
        z_prev = z_cur;
        r_prev = r_cur;
    }
    return x_prev;

}

Vector ConjugateGradientInPlaceSolver::subtract(Vector a, Vector &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] -= b[i];
    }
    return a;
}

Vector ConjugateGradientInPlaceSolver::sum(Vector a, Vector &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] += b[i];
    }
    return a;
}

double ConjugateGradientInPlaceSolver::scalar_product(Vector &a, Vector &b) {
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

Vector ConjugateGradientInPlaceSolver::multiply(Vector v, double x) {
    for (double &i : v) {
        i *= x;
    }
    return v;
}
