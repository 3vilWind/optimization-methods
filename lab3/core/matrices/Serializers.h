#pragma once

#include "SymmetricProfileMatrix.h"
#include "SparseRowColumnMatrix.h"
#include "DenseMatrix.h"


void serialize(const SymmetricProfileMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "wb");

    size_t n = matrix.size();
    size_t rowLowerProfileSize = matrix.rowLowerProfile.size();
    size_t columnUpperProfileSize = matrix.columnUpperProfile.size();

    fwrite(&n, sizeof(size_t), 1, f);
    fwrite(&rowLowerProfileSize, sizeof(size_t), 1, f);
    fwrite(&columnUpperProfileSize, sizeof(size_t), 1, f);

    fwrite(matrix.diagonal.data(), sizeof(double), n, f);

    fwrite(matrix.rowLowerProfile.data(), sizeof(double), rowLowerProfileSize, f);

    fwrite(matrix.columnUpperProfile.data(), sizeof(double), columnUpperProfileSize, f);
    fwrite(matrix.index.data(), sizeof(size_t), n + 1, f);

    fclose(f);
}

void deserialize(SymmetricProfileMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "rb");

    size_t n, rowLowerProfileSize, columnUpperProfileSize;

    fread(&n, sizeof(size_t), 1, f);
    fread(&rowLowerProfileSize, sizeof(size_t), 1, f);
    fread(&columnUpperProfileSize, sizeof(size_t), 1, f);

    matrix.resize(n, rowLowerProfileSize, columnUpperProfileSize);

    fread(matrix.diagonal.data(), sizeof(double), n, f);
    fread(matrix.rowLowerProfile.data(), sizeof(double), rowLowerProfileSize, f);
    fread(matrix.columnUpperProfile.data(), sizeof(double), columnUpperProfileSize, f);
    fread(matrix.index.data(), sizeof(size_t), n + 1, f);

    fclose(f);
}


void serialize(const std::vector<double> &vec, const std::string &path) {
    FILE *f = fopen(path.c_str(), "wb");

    size_t n = vec.size();

    fwrite(&n, sizeof(n), 1, f);
    fwrite(vec.data(), sizeof(double), n, f);

    fclose(f);
}

void deserialize(std::vector<double> &vec, const std::string &path) {
    FILE *f = fopen(path.c_str(), "rb");
    size_t n;

    fread(&n, sizeof(n), 1, f);

    vec.resize(n);
    fread(vec.data(), sizeof(double), n, f);

    fclose(f);
}
