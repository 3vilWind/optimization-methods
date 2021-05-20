#include "SparseRowColumnMatrix.h"

SparseRowColumnMatrix::SparseRowColumnMatrix(DenseMatrix matrix) {
    indexFirst.push_back(0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        size_t cnt = 0;
        diagonal.push_back(matrix.get(i, i));
        for (size_t j = 0; j < i; ++j) {
            if (matrix.get(i, j) != 0) {
                ++cnt;
                rowLowerProfile.push_back(matrix.get(i, j));
                columnUpperProfile.push_back(matrix.get(j, i));
                indexNonZero.push_back(j);
            }
        }
        indexFirst.push_back(cnt);
    }
}

double SparseRowColumnMatrix::get(size_t x, size_t y) const {
    if (x == y) {
        return diagonal[x];
    }
    if (x > y) {
        for (size_t i = indexFirst[x]; i < indexFirst[x + 1]; ++i) {
            if (i == y) {
                return rowLowerProfile[i];
            }
        }
    } else {
        for (size_t i = indexFirst[y]; i < indexFirst[y + 1]; ++i) {
            if (i == x) {
                return columnUpperProfile[i];
            }
        }
    }
    return 0;
}

void SparseRowColumnMatrix::set(size_t x, size_t y, double value) {
    if (x == y) {
        diagonal[x] = value;
    }
    if (x > y) {
        for (size_t i = indexFirst[x]; i < indexFirst[x + 1]; ++i) {
            if (i == y) {
                rowLowerProfile[i] = value;
                return;
            }
        }
    } else {
        for (size_t i = indexFirst[y]; i < indexFirst[y + 1]; ++i) {
            if (i == x) {
                columnUpperProfile[i] = value;
                return;
            }
        }
    }
}
