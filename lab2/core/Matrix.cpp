#include "Matrix.h"

Matrix::Matrix(std::vector<Vector> matrix) : matrix(matrix) {}

size_t Matrix::number_of_columns() const {
    return matrix.empty() ? 0 : matrix.at(0).size();
}

size_t Matrix::number_of_rows() const {
    return matrix.size();
}

Vector Matrix::row(size_t index) const {
    return Vector(matrix.at(index));
}

Vector Matrix::vector_multiplication(const Vector& v) const {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v.scalar_multiplication(this->row(i)));
    }
    return Vector(ans);
}
