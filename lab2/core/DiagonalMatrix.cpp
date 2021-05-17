#include "DiagonalMatrix.h"

#include <utility>
#include "Utils.h"

DiagonalMatrix::DiagonalMatrix(size_t size, double k) {
    std::vector<double> ans;
    ans.push_back(1);
    for (size_t i = 1; i < size - 1; ++i) {
        ans.push_back(random(1, k));
    }
    ans.push_back(k);
    diagonal = Vector(ans);
}

DiagonalMatrix::DiagonalMatrix(Vector diagonal) : diagonal(std::move(diagonal)) {}

size_t DiagonalMatrix::number_of_columns() const {
    return diagonal.size();
}

size_t DiagonalMatrix::number_of_rows() const {
    return diagonal.size();
}

Vector DiagonalMatrix::row(size_t index) const {
    std::vector<double> ans(diagonal.size(), 0);
    ans[index] = diagonal.get(index);
    return Vector(ans);
}

Vector DiagonalMatrix::vector_multiplication(const Vector& v) const {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v.get(i) * diagonal.get(i));
    }
    return Vector(ans);
}