#include "../matrices/DenseMatrix.h"
#include "../matrices/SymmetricSparseRowColumnMatrix.h"
#include <gtest/gtest.h>
#include "Utils.h"

class SymmetricSparseRowColumnTest : public SymmetricSparseRowColumnMatrix {
    using SymmetricSparseRowColumnMatrix::SymmetricSparseRowColumnMatrix;

    FRIEND_TEST(SparseRowColumnTests, createFromDense02);

    FRIEND_TEST(SparseRowColumnTests, createFromDense03);
};


TEST(SparseRowColumnTests, createFromDense01) {
    DenseMatrix matrix({
                               {1, 2, 3,  4},
                               {2, 6, 7,  8},
                               {3, 7, 11, 12},
                               {4, 8, 12, 16}
                       });

    SymmetricSparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);
}


TEST(SparseRowColumnTests, createFromDense02) {
    DenseMatrix matrix({
                               {1, 0, 0},
                               {0, 5, 5},
                               {0, 5, 9}
                       });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> indexFirst({0, 0, 0, 1});
    std::vector<size_t> indexNonZero({1});

    SymmetricSparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.indexFirst, indexFirst);
    expectEqualVectors(a.indexNonZero, indexNonZero);
    EXPECT_EQ(a.rowLowerProfile.size(), 1);
}


TEST(SparseRowColumnTests, createFromDense03) {
    DenseMatrix matrix({
                               {1, 2, 3,  4},
                               {2, 6, 0,  0},
                               {3, 0, 11, 2},
                               {4, 0, 2,  16}
                       });
    std::vector<double> diagonal({1, 6, 11, 16});
    std::vector<size_t> indexFirst({0, 0, 1, 2, 4});
    std::vector<double> rowLower({2, 3, 4, 2});
    std::vector<size_t> indexNonZero({0, 0, 0, 2});

    SymmetricSparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.rowLowerProfile, rowLower);
    expectEqualVectors(a.indexFirst, indexFirst);
    expectEqualVectors(a.indexNonZero, indexNonZero);
}


