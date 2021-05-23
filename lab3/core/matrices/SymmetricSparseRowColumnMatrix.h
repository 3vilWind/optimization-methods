#pragma once

#include "Matrix.h"
#include <vector>
#include "DenseMatrix.h"

class SymmetricSparseRowColumnMatrix : public Matrix {
protected:
    std::vector<double> diagonal;
    std::vector<double> rowLowerProfile;
    std::vector<size_t> indexFirst;
    std::vector<size_t> indexNonZero;
public:
    SymmetricSparseRowColumnMatrix() = default;
    SymmetricSparseRowColumnMatrix(size_t n) {
        diagonal.resize(n, 0);
        indexFirst.push_back(0);
    }

    explicit SymmetricSparseRowColumnMatrix(const Matrix &matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    std::vector<double> multiply(std::vector<double> &v);

    size_t size() const override;

    void resize(size_t n, size_t rowLowerProfileSize, size_t indexNonZeroSize) {
        diagonal.resize(n, 0);
        rowLowerProfile.resize(rowLowerProfileSize, 0);
        indexFirst.resize(n + 1, 0);
        indexNonZero.resize(indexNonZeroSize, 0);
    }

    void insertLine(const std::vector<double>& line);


    friend void deserialize(SymmetricSparseRowColumnMatrix &matrix, const std::string &path);

    friend void serialize(const SymmetricSparseRowColumnMatrix &matrix, const std::string &path);
};
