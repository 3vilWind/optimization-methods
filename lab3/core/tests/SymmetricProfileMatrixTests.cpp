#include "../matrices/DenseMatrix.h"
#include "../matrices/SymmetricProfileMatrix.h"
#include <gtest/gtest.h>
#include "Utils.h"

class SymmetricProfileMatrixTest : public SymmetricProfileMatrix {
    using SymmetricProfileMatrix::SymmetricProfileMatrix;

    FRIEND_TEST(SymmetricProfileMatrixTests, createFromDense02);

    FRIEND_TEST(SymmetricProfileMatrixTests, createFromDense03);

    FRIEND_TEST(SymmetricProfileMatrixTests, createFromDense04);
};


TEST(SymmetricProfileMatrixTests, createFromDense01) {
    DenseMatrix denseMatrix({
                                    {1, 2, 3},
                                    {4, 5, 6},
                                    {7, 8, 9}
                            });

    SymmetricProfileMatrixTest a(denseMatrix);
    expectEqualMatrices(a, denseMatrix);
}


TEST(SymmetricProfileMatrixTests, createFromDense02) {
    DenseMatrix denseMatrix({
                                    {1, 0, 0},
                                    {0, 5, 0},
                                    {0, 0, 9}
                            });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> index({0, 0, 0, 0});

    SymmetricProfileMatrixTest a(denseMatrix);
    expectEqualMatrices(a, denseMatrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.index, index);
    EXPECT_EQ(a.rowLowerProfile.size(), 0);
    EXPECT_EQ(a.columnUpperProfile.size(), 0);
}


TEST(SymmetricProfileMatrixTests, createFromDense03) {
    DenseMatrix denseMatrix({
                                    {1,  0, 1},
                                    {0,  5, 0},
                                    {11, 0, 9}
                            });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> index({0, 0, 0, 2});

    SymmetricProfileMatrixTest a(denseMatrix);
    expectEqualMatrices(a, denseMatrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.index, index);
    EXPECT_EQ(a.rowLowerProfile.size(), 2);
    EXPECT_EQ(a.columnUpperProfile.size(), 2);
}

TEST(SymmetricProfileMatrixTests, createFromDense04) {
    DenseMatrix denseMatrix({
                                    {1,  0, 1},
                                    {0,  0, 0},
                                    {11, 0, 9}
                            });
    std::vector<double> diagonal({1, 0, 9});
    std::vector<size_t> index({0, 0, 0, 2});

    SymmetricProfileMatrixTest a(denseMatrix);
    expectEqualMatrices(a, denseMatrix);

    expectEqualVectors(a.diagonal, diagonal);
    expectEqualVectors(a.index, index);
    EXPECT_EQ(a.rowLowerProfile.size(), 2);
    EXPECT_EQ(a.columnUpperProfile.size(), 2);
}