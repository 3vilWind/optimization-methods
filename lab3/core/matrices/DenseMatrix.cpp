#include "DenseMatrix.h"

#include <utility>

DenseMatrix::DenseMatrix(std::vector<std::vector<double>> matrix) : matrix(std::move(matrix)) {}

double DenseMatrix::get(size_t x, size_t y) const {
    return matrix[x][y];
}

void DenseMatrix::set(size_t x, size_t y, double value) {
    matrix[x][y] = value;
}

size_t DenseMatrix::size() const {
    return matrix.size();
}
