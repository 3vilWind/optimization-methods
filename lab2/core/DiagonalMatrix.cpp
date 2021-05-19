#include "DiagonalMatrix.h"

#include <utility>
#include <lab2/core/include/jacobi_pd.hpp>
#include "Utils.h"

DiagonalMatrix::DiagonalMatrix(Vector diagonal) : diagonal(std::move(diagonal)) {}

size_t DiagonalMatrix::size() const {
    return diagonal.size();
}

Vector DiagonalMatrix::row(size_t index) const {
    std::vector<double> ans(diagonal.size(), 0);
    ans[index] = diagonal.get(index);
    return Vector(ans);
}

Vector DiagonalMatrix::mulByVector(const Vector& v) const {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v.get(i) * diagonal.get(i));
    }
    return Vector(ans);
}


DiagonalMatrix DiagonalMatrix::getRandomMatrix(size_t size, double k) {
    std::vector<double> ans;
    ans.push_back(1);
    for (size_t i = 1; i < size - 1; ++i) {
        ans.push_back(random(1, k));
    }
    ans.push_back(k);
    return DiagonalMatrix(Vector(ans));
}

double DiagonalMatrix::getMaxEigenValue() const {
    auto vec = diagonal.getPlainVector();
    return *std::max_element(vec.begin(), vec.end());
}
