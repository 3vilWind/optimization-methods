#pragma once

#include <vector>
#include <string>
#include "Matrix.h"
#include "DenseMatrix.h"


class SymmetricProfileMatrix : public Matrix {
protected:
    std::vector<double> diagonal;
    std::vector<double> rowLowerProfile;
    std::vector<double> columnUpperProfile;
    std::vector<size_t> index;

    size_t getShift(size_t a) const;

    size_t getProfileIndex(size_t shift, size_t a, size_t b) const;


    void resize(size_t n, size_t rowLowerProfileSize, size_t columnUpperProfileSize) {
        diagonal.resize(n, 0);
        rowLowerProfile.resize(rowLowerProfileSize, 0);
        columnUpperProfile.resize(columnUpperProfileSize, 0);
        index.resize(n + 1, 0);
    }

public:
    SymmetricProfileMatrix() = default;

    explicit SymmetricProfileMatrix(const Matrix &matrix);

    double get(size_t y, size_t x) const override;

    void set(size_t y, size_t x, double value) override;

    size_t size() const override;

    friend void serialize(const SymmetricProfileMatrix &matrix, const std::string &path);

    friend void deserialize(SymmetricProfileMatrix &matrix, const std::string &path);
};