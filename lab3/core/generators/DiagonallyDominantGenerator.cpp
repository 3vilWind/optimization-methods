#include "DiagonallyDominantGenerator.h"
#include <random>
#include <vector>
#include <tuple>

std::tuple<DenseMatrix, std::vector<double>> DiagonallyDominantGenerator::generate(size_t n, size_t k) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-4, 0);
    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0));
    A[0][0] = pow(10, -k);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                A[i][j] = dis(gen);
                A[i][i] -= A[i][j];
            }
        }
    }
    std::vector<double> x;
    for (size_t i = 0; i < n; ++i) {
        x.push_back(i + 1);
    }
    std::vector<double> b(n, 0);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            b[i] += A[i][j] * x[j];
        }
    }
    auto flex = DenseMatrix(A);
    return  std::make_tuple(flex, b);
}
