#include "DenseMatrix.h"

#include <utility>

DenseMatrix::DenseMatrix(std::vector<std::vector<double>> matrix) : matrix(std::move(matrix)) {}

double DenseMatrix::get(size_t y, size_t x) const {
    return matrix[y][x];
}

void DenseMatrix::set(size_t y, size_t x, double value) {
    matrix[y][x] = value;
}

size_t DenseMatrix::size() const {
    return matrix.size();
}
