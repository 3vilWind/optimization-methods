#include "HilbertGenerator.h"

DenseMatrix generateHilbertMatrix(size_t k) {
    std::vector<std::vector<double>> A(k, std::vector<double>(k, 0));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A[i][j] = 1.0 / (i + j + 1);
        }
    }

    return DenseMatrix(A);
}
