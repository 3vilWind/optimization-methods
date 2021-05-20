#include "SymmetricProfileMatrix.h"

SymmetricProfileMatrix::SymmetricProfileMatrix(std::vector<std::vector<double>> matrix) {
    index.push_back(0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        diagonal.push_back(matrix[i][i]);
        size_t j = 0;
        while (matrix[i][j] == 0) {
            ++j;
        }
        index.push_back(i - j + index[i]);
        for (; j < i; ++j) {
            rowLowerProfile.push_back(matrix[i][j]);
            columnUpperProfile.push_back(matrix[j][i]);
        }
    }
}

double SymmetricProfileMatrix::get(size_t x, size_t y) const {
    if (x == y) {
        return diagonal[x];
    }
    if (x > y) {
        size_t profile = index[x + 1] - index[x];
        return (y < x - profile ? 0 : rowLowerProfile[index[x] + y - (x - profile) - 1]);
    } else {
        size_t profile = index[y + 1] - index[y];
        return (x < y - profile ? 0 : columnUpperProfile[index[y] + x - (y - profile) - 1]);
    }
}

void SymmetricProfileMatrix::set(size_t x, size_t y, double value) {
    if (x == y) {
        diagonal[x] = value;
    }
    if (x > y) {
        size_t profile = index[x + 1] - index[x];
        rowLowerProfile[index[x] + y - (x - profile) - 1] = value;
    } else {
        size_t profile = index[y + 1] - index[y];
        columnUpperProfile[index[y] + x - (y - profile) - 1] = value;
    }
}
