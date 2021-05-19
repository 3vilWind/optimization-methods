#include "Matrix.h"

#include <utility>
#include <lab2/core/include/jacobi_pd.hpp>

Matrix::Matrix(std::vector<Vector> matrix) : matrix(std::move(matrix)) {}

size_t Matrix::size() const {
    return matrix.size();
}

Vector Matrix::row(size_t index) const {
    return Vector(matrix.at(index));
}

Vector Matrix::mulByVector(const Vector& v) const {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v * this->row(i));
    }
    return Vector(ans);
}

double Matrix::getMaxEigenValue() const {
    std::vector<std::vector<double>> matrix;
    matrix.reserve(size());
    for (int i = 0; i < size(); ++i) {
        matrix.emplace_back(row(i).getPlainVector());
    }
    std::vector<double> eigenValues(size(), 0);
    std::vector<std::vector<double>> eigenVectors(size(),
                                                  std::vector<double>(size(), 0));
    typedef jacobi_pd::Jacobi<double,
            std::vector<double> &,
            std::vector<std::vector<double>> &,
            const std::vector<std::vector<double>> &> Jacobi;
    Jacobi eigenCalc(size());

    eigenCalc.Diagonalize(matrix, eigenValues, eigenVectors, Jacobi::SORT_DECREASING_EVALS, false);
    return eigenValues[0];
}
