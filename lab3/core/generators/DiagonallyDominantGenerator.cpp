#include "DiagonallyDominantGenerator.h"
#include <random>
#include <vector>
#include <cmath>


bool checkDiagonalHasNoZeroes(const std::vector<std::vector<double>> &matrix) {
    for (int i = 0; i < matrix.size(); ++i)
        if (matrix[i][i] == 0.0)
            return false;
    return true;
}


DenseMatrix generateDiagonallyDominantMatrix(size_t n, size_t k) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-4, 0);
    std::uniform_int_distribution<> disWithoutZero(-4, -1);

    while (true) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n, 0));
        A[0][0] = pow(10.0, -(double) k);

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                A[i][j] = dis(gen);
                if (A[i][j] != 0.0)
                    A[j][i] = disWithoutZero(gen);
            }
        }

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    A[i][i] -= A[i][j];
                }
            }
        }

        if (checkDiagonalHasNoZeroes(A))
            return DenseMatrix(A);
    }
}
