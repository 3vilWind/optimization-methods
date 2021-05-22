#include "Utils.h"

std::vector<double> generateB(const Matrix &A, const std::vector<double> &x) {
    std::vector<double> b(x.size(), 0);
    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < x.size(); ++j) {
            b[i] += A.get(i, j) * x[j];
        }
    }
    return b;
}


std::vector<double> generateIncrementalVector(size_t n) {
    std::vector<double> x(n, 0);
    for (size_t i = 0; i < n; ++i) {
        x[i] = i + 1;
    }
    return x;
}