#include "SymmetricSparseRowColumnMatrix.h"

SymmetricSparseRowColumnMatrix::SymmetricSparseRowColumnMatrix(const Matrix &matrix) {
    indexFirst.push_back(0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        size_t cnt = 0;
        diagonal.push_back(matrix.get(i, i));
        for (size_t j = 0; j < i; ++j) {
            if (matrix.get(i, j) != 0) {
                ++cnt;
                rowLowerProfile.push_back(matrix.get(i, j));
                indexNonZero.push_back(j);
            }
        }
        indexFirst.push_back(cnt + indexFirst[i]);
    }
}

double SymmetricSparseRowColumnMatrix::get(size_t x, size_t y) const {
    if (x == y) {
        return diagonal[x];
    }
    if (x < y)
        std::swap(x, y);

    for (size_t i = indexFirst[x]; i < indexFirst[x + 1]; ++i) {
        if (indexNonZero[i] == y) {
            return rowLowerProfile[i];
        }
    }
    return 0;
}

void SymmetricSparseRowColumnMatrix::set(size_t x, size_t y, double value) {
    if (x == y) {
        diagonal[x] = value;
        return;
    }
    if (x < y)
        std::swap(x, y);

    for (size_t i = indexFirst[x]; i < indexFirst[x + 1]; ++i) {
        if (indexNonZero[i] == y) {
            rowLowerProfile[i] = value;
            return;
        }
    }
}

size_t SymmetricSparseRowColumnMatrix::size() const {
    return diagonal.size();
}

std::vector<double> SymmetricSparseRowColumnMatrix::multiply(std::vector<double> &v) {
    size_t pos = 0;
    std::vector<double> ans(v.size(), 0);
    for (size_t i = 0; i < v.size(); ++i) {
        size_t cnt = this->indexFirst[i + 1] - this->indexFirst[i];
        for (size_t j = pos; j < cnt + pos; ++j) {
            size_t col = this->indexNonZero[j];
            ans[col] += this->rowLowerProfile[j] * v[i];
            ans[i] += this->rowLowerProfile[j] * v[col];
        }
        ans[i] += this->diagonal[i] * v[i];
        pos += cnt;
    }
    return ans;
}

void SymmetricSparseRowColumnMatrix::insertLine(const std::vector<double> &line) {
    size_t cnt = 0;
    for (size_t j = 0; j < line.size(); ++j) {
        if (line[j] != 0) {
            ++cnt;
            rowLowerProfile.push_back(line[j]);
            indexNonZero.push_back(j);
        }
    }
    indexFirst.push_back(cnt + indexFirst[line.size()]);
}
