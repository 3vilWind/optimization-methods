#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(std::vector<std::vector<double>> matrix) : matrix(matrix) {}

double DenseMatrix::get(size_t x, size_t y) const {
    return matrix[x][y];
}

void DenseMatrix::set(size_t x, size_t y, double value) {
    matrix[x][y] = value;
}

