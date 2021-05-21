#include "SymmetricProfileMatrix.h"
#include <stdexcept>
#include <algorithm>


SymmetricProfileMatrix::SymmetricProfileMatrix(const Matrix &matrix) {
    index.push_back(0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        diagonal.push_back(matrix.get(i, i));
        size_t j = 0;
        while (matrix.get(i, j) == 0) {
            ++j;
        }
        index.push_back(i - j + index[i]);
        for (; j < i; ++j) {
            rowLowerProfile.push_back(matrix.get(i, j));
            columnUpperProfile.push_back(matrix.get(j, i));
        }
    }
}

double SymmetricProfileMatrix::get(size_t y, size_t x) const {
    if (x == y) {
        return diagonal[x];
    }
    if (x < y) {
        size_t shift = getShift(y);
        return (x < shift ? 0 : rowLowerProfile[getProfileIndex(shift, y, x)]);
    } else {
        size_t shift = getShift(x);
        return (y < shift ? 0 : columnUpperProfile[getProfileIndex(shift, x, y)]);
    }
}

void SymmetricProfileMatrix::set(size_t y, size_t x, double value) {
    if (x == y) {
        diagonal[x] = value;
        return;
    }
    if (x < y) {
        size_t shift = getShift(y);
        if (x < shift && value != 0.0)
            throw std::range_error("write outside profile");
        rowLowerProfile[getProfileIndex(shift, y, x)] = value;
    } else {
        size_t shift = getShift(x);
        if (y < shift && value != 0.0)
            throw std::range_error("write outside profile");
        columnUpperProfile[getProfileIndex(shift, x, y)] = value;
    }
}

size_t SymmetricProfileMatrix::size() const {
    return diagonal.size();
}

size_t SymmetricProfileMatrix::getShift(size_t a) const {
    return a - (index[a + 1] - index[a]);
}

size_t SymmetricProfileMatrix::getProfileIndex(size_t shift, size_t a, size_t b) const {
    return index[a] + b - shift;
}

void SymmetricProfileMatrix::serialize(const std::string &path) const {
    FILE *f = fopen(path.c_str(), "w");
    size_t n = size();
    fprintf(f, "%u %u %u\n", n, rowLowerProfile.size(), columnUpperProfile.size());
    for (double i : diagonal)
        fprintf(f, "%le ", i);
    fprintf(f, "\n");

    for (double i : rowLowerProfile)
        fprintf(f, "%le ", i);
    fprintf(f, "\n");

    for (double i : columnUpperProfile)
        fprintf(f, "%le ", i);
    fprintf(f, "\n");

    for (size_t i : index)
        fprintf(f, "%u ", i);
    fprintf(f, "\n");
}

SymmetricProfileMatrix SymmetricProfileMatrix::deserialize(const std::string &path) {
    FILE *f = fopen(path.c_str(), "r");
    size_t n, rowLowerProfileSize, columnUpperProfileSize;
    fscanf(f, "%u %u %u", &n, &rowLowerProfileSize, &columnUpperProfileSize);

    SymmetricProfileMatrix m(n, rowLowerProfileSize, columnUpperProfileSize);
    for (size_t i = 0; i < n; ++i)
        fscanf(f, "%le", &m.diagonal[i]);

    for (size_t i = 0; i < rowLowerProfileSize; ++i)
        fscanf(f, "%le", &m.rowLowerProfile[i]);

    for (size_t i = 0; i < columnUpperProfileSize; ++i)
        fscanf(f, "%le", &m.columnUpperProfile[i]);

    for (size_t i = 0; i < n + 1; ++i)
        fscanf(f, "%u", &m.index[i]);

    return m;
}
