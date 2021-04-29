#include "Matrix.h"

Matrix::Matrix(std::vector<Vector> matrix) : matrix(matrix) {}

size_t Matrix::number_of_columns() {
    return matrix.empty() ? 0 : matrix.at(0).size();
}

size_t Matrix::number_of_rows() {
    return matrix.size();
}

Vector Matrix::row(size_t index) {
    return Vector(matrix.at(index));
}

Vector Matrix::vector_multiplication(Vector v) {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v.scalar_multiplication(this->row(i)));
    }
    return Vector(ans);
}
