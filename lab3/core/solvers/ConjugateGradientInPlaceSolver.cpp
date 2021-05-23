#include "ConjugateGradientInPlaceSolver.h"
#include "../matrices/SymmetricSparseRowColumnMatrix.h"
#include <vector>
#include <cmath>
#include <stdexcept>
#include <typeinfo>
#include "VectorUtils.h"

std::vector<double> ConjugateGradientInPlaceSolver::solve(Matrix &a, std::vector<double> b, double epsilon) {
    if (typeid(a) != typeid(SymmetricSparseRowColumnMatrix)) {
        throw std::runtime_error("Only Sparse Matrices are supported!");
    }
    auto &matrix = dynamic_cast<SymmetricSparseRowColumnMatrix &>(a);
    Vector x_prev(a.size(), 0);
    x_prev[0] = 1;
    Vector mx = matrix.multiply(x_prev);
    Vector r_prev = subtract(b, mx);
    Vector z_prev = r_prev;
    for (size_t i = 1; i < 1e4; ++i) {
        Vector mz = matrix.multiply(z_prev);
        double alpha = scalar_product(r_prev, r_prev) / scalar_product(mz, z_prev);
        Vector x_cur = sum(multiply(z_prev, alpha), x_prev);
        Vector mz_alpha = multiply(mz, alpha);
        Vector r_cur = subtract(r_prev, mz_alpha);
        double beta = scalar_product(r_cur, r_cur) / scalar_product(r_prev, r_prev);
        Vector z_cur = sum(multiply(z_prev, beta), r_cur);
        if ((scalar_product(r_cur, r_cur) / scalar_product(b, b)) < epsilon * epsilon) {
            return x_cur;
        }
        x_prev = x_cur;
        z_prev = z_cur;
        r_prev = r_cur;
    }
    return x_prev;
}

