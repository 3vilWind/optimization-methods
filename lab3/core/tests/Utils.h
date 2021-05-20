#include <gtest/gtest.h>
#include "../matrices/Matrix.h"


void expect_equal_matrices(const Matrix &a, const Matrix &b) {
    EXPECT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            EXPECT_DOUBLE_EQ(a.get(i, j), b.get(i, j));
        }
    }
}

void expect_equal_vectors(const std::vector<double> &a, const std::vector<double> &b) {
    EXPECT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        EXPECT_DOUBLE_EQ(a[i], b[i]);
    }
}

void expect_equal_vectors(const std::vector<size_t> &a, const std::vector<size_t> &b) {
    EXPECT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}