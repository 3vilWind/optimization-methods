#include "GaussPivotingInPlaceSolver.h"
#include <cfloat>
#include <algorithm>
#include <iostream>


std::vector<double> GaussPivotingInPlaceSolver::solve(Matrix &a, std::vector<double> b) {
    for (size_t k = 0; k < a.size() - 1; ++k) {
        std::cout << "\n";
        double max = 0;
        size_t row_index = k;
        for (size_t i = k; i < a.size(); ++i) {
            if (std::abs(max) < std::abs(a.get(i, k))) {
                max = a.get(i, k);
                row_index = i;
            }
        }
        /*if (max < eps) {
            // нет решения
        }*/
        swap_rows(a, k, row_index);
        std::swap(b[k], b[row_index]);

        for (size_t i = k + 1; i < a.size(); ++i) {
            double m = a.get(i, k) / max;
            subtract_rows(a, i, k, k, a.size(), m);
            b[i] -= b[k] * m;
        }
    }
    return reverse_gauss(a, b);
}

void GaussPivotingInPlaceSolver::swap_rows(Matrix &a, size_t row1, size_t row2) {
    if (row1 == row2) {
        return;
    }
    for (size_t col = 0; col < a.size(); ++col) {
        double c = a.get(row1, col), d = a.get(row2, col);
        a.set(row1, col, d);
        a.set(row2, col, c);
    }
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
