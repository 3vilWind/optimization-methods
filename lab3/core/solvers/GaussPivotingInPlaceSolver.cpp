#include "GaussPivotingInPlaceSolver.h"
#include <cfloat>
#include <algorithm>
#include <typeinfo>
#include "../matrices/DenseMatrix.h"
#include <stdexcept>


std::vector<double> GaussPivotingInPlaceSolver::solve(Matrix &a, std::vector<double> b) {
    if (typeid(a) != typeid(DenseMatrix)) {
        throw std::runtime_error("Only Dense Matrices are supported!");
    }
    auto &matrix = dynamic_cast<DenseMatrix &>(a);

    for (size_t k = 0; k < matrix.size() - 1; ++k) {
        double max = 0;
        size_t row_index = k;
        for (size_t i = k; i < matrix.size(); ++i) {
            if (std::abs(max) < std::abs(matrix.get(i, k))) {
                max = matrix.get(i, k);
                row_index = i;
            }
        }
        /*if (max < eps) {
            // нет решения
        }*/
        matrix.swap_rows(k, row_index);
        std::swap(b[k], b[row_index]);

        for (size_t i = k + 1; i < matrix.size(); ++i) {
            double m = matrix.get(i, k) / max;
            subtract_rows(matrix, i, k, k, matrix.size(), m);
            b[i] -= b[k] * m;
        }
    }
    return reverse_gauss(matrix, b);
}

void
GaussPivotingInPlaceSolver::subtract_rows(Matrix &a, size_t row1, size_t row2, size_t from, size_t to, double value) {
    for (size_t col = from; col < to; ++col) {
        double new_value = a.get(row1, col) - a.get(row2, col) * value;
        a.set(row1, col, new_value);
    }
}

std::vector<double> GaussPivotingInPlaceSolver::reverse_gauss(Matrix &a, std::vector<double> &b) {
    std::vector<double> ans(a.size(), 0);
    for (int i = a.size() - 1; i >= 0; --i) {
        double res = b[i];
        for (size_t j = i + 1; j < a.size(); ++j) {
            res -= a.get(i, j) * ans[j];
        }
        res /= a.get(i, i);
        ans[i] = res;
    }
    return ans;
}
