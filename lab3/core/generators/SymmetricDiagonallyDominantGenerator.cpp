#include <random>
#include "SymmetricDiagonallyDominantGenerator.h"

SymmetricSparseRowColumnMatrix generateSymmetricDiagonallyDominantMatrix(size_t n, bool invertSignOffDiagonal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-4, 0);
    std::uniform_int_distribution<> disIsZero(1, 10);
    std::uniform_int_distribution<> disWithoutZero(-4, 0);
    if (invertSignOffDiagonal)
        dis = std::uniform_int_distribution<>(0, 4);


    SymmetricSparseRowColumnMatrix result(n);
    result.set(0, 0, 1);
    std::vector<double> sums(n, 0);

    for (size_t i = 0; i < n; ++i) {
        std::vector<double> line(i, 0);
        for (size_t j = 0; j < i; ++j) {
            double x = 0;
//            if (disIsZero(gen) >= 9)
            x = dis(gen);
            line[j] = x;

            result.set(i, i, result.get(i, i) - x);
            result.set(j, j, result.get(j, j) - x);
        }
        result.insertLine(line);
    }

    return result;
}


DenseMatrix generateSymmetricDiagonallyDominantDenseMatrix(size_t n, bool invertSignOffDiagonal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-4, 0);
    if (invertSignOffDiagonal)
        dis = std::uniform_int_distribution<>(0, 4);

    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0));
    A[0][0] = 1;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            A[i][j] = dis(gen);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                A[i][i] -= A[i][j];
            }
        }
    }

    return DenseMatrix(A);
}