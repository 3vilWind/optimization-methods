#include "../matrices/DenseMatrix.h"
#include "../matrices/SparseRowColumnMatrix.h"
#include <gtest/gtest.h>
#include "Utils.h"

class SparseRowColumnTest : public SparseRowColumnMatrix {
    using SparseRowColumnMatrix::SparseRowColumnMatrix;

    FRIEND_TEST(SparseRowColumnTests, createFromDense02);

    FRIEND_TEST(SparseRowColumnTests, createFromDense03);
};


TEST(SparseRowColumnTests, createFromDense01) {
    DenseMatrix matrix({
                                    {1,  2,   3, 4},
                                    {5,  6,   7, 8},
                                    {9,  10, 11, 12},
                                    {13, 14, 15, 16}
                            });

    SparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);
}


TEST(SparseRowColumnTests, createFromDense02) {
    DenseMatrix matrix({
                                    {1, 0, 0},
                                    {0, 5, 5},
                                    {0, 1, 9}
                            });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> indexFirst({0, 0, 0, 1});
    std::vector<size_t> indexNonZero({1});

    SparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.indexFirst, indexFirst);
    expectEqualVectors(a.indexNonZero, indexNonZero);
    EXPECT_EQ(a.rowLowerProfile.size(), 1);
    EXPECT_EQ(a.columnUpperProfile.size(), 1);
}


TEST(SparseRowColumnTests, createFromDense03) {
    DenseMatrix matrix({
                               {1,  2,  3, 4},
                               {5,  6,  0, 0},
                               {9,  0,  11, 2},
                               {13, 0,  3, 16}
                       });
    std::vector<double> diagonal({1, 6, 11, 16});
    std::vector<size_t> indexFirst({0, 0, 1, 2, 4});
    std::vector<double> rowLower({5, 9, 13, 3});
    std::vector<double> columnUpper({2, 3, 4, 2});
    std::vector<size_t> indexNonZero({0, 0, 0, 2});

    SparseRowColumnTest a(matrix);
    expectEqualMatrices(a, matrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.rowLowerProfile, rowLower);
    expectEqualVectors(a.columnUpperProfile, columnUpper);
    expectEqualVectors(a.indexFirst, indexFirst);
    expectEqualVectors(a.indexNonZero, indexNonZero);
}


