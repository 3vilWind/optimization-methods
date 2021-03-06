#pragma once

#include "SymmetricProfileMatrix.h"
#include "SymmetricSparseRowColumnMatrix.h"
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

void serialize(const SymmetricSparseRowColumnMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "wb");

    size_t n = matrix.size();
    size_t rowLowerProfileSize = matrix.rowLowerProfile.size();
    size_t indexNonZeroSize = matrix.indexNonZero.size();

    fwrite(&n, sizeof(size_t), 1, f);
    fwrite(&rowLowerProfileSize, sizeof(size_t), 1, f);
    fwrite(&indexNonZeroSize, sizeof(size_t), 1, f);

    fwrite(matrix.diagonal.data(), sizeof(double), n, f);
    fwrite(matrix.rowLowerProfile.data(), sizeof(double), rowLowerProfileSize, f);
    fwrite(matrix.indexFirst.data(), sizeof(size_t), n + 1, f);
    fwrite(matrix.indexNonZero.data(), sizeof(size_t), indexNonZeroSize, f);
    fclose(f);
}

void deserialize(SymmetricSparseRowColumnMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "rb");

    size_t n, rowLowerProfileSize, columnUpperProfileSize, indexNonZeroSize;

    fread(&n, sizeof(size_t), 1, f);
    fread(&rowLowerProfileSize, sizeof(size_t), 1, f);
    fread(&indexNonZeroSize, sizeof(size_t), 1, f);

    matrix.resize(n, rowLowerProfileSize, indexNonZeroSize);

    fread(matrix.diagonal.data(), sizeof(double), n, f);
    fread(matrix.rowLowerProfile.data(), sizeof(double), rowLowerProfileSize, f);
    fread(matrix.indexFirst.data(), sizeof(size_t), n + 1, f);
    fread(matrix.indexNonZero.data(), sizeof(size_t), indexNonZeroSize, f);

    fclose(f);
}

void serialize(const DenseMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "wb");

    size_t n = matrix.size();
    fwrite(&n, sizeof(size_t), 1, f);

    for (int i = 0; i < n; ++i) {
        fwrite(matrix.matrix[i].data(), sizeof(double), n, f);
    }

    fclose(f);
}

void deserialize(DenseMatrix &matrix, const std::string &path) {
    FILE *f = fopen(path.c_str(), "rb");

    size_t n;

    fread(&n, sizeof(size_t), 1, f);
    matrix.matrix.resize(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        fread(matrix.matrix[i].data(), sizeof(double), n, f);
    }

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
