#include "../matrices/DenseMatrix.h"
#include "../matrices/SymmetricProfileMatrix.h"
#include <gtest/gtest.h>
#include "Utils.h"

class SymmetricProfileMatrixTest : public SymmetricProfileMatrix {
    using SymmetricProfileMatrix::SymmetricProfileMatrix;

    FRIEND_TEST(SymmetricProfileMatrixTests, create_from_dense_02);
    FRIEND_TEST(SymmetricProfileMatrixTests, create_from_dense_03);
};


TEST(SymmetricProfileMatrixTests, create_from_dense_01) {
    DenseMatrix denseMatrix({
                                    {1, 2, 3},
                                    {4, 5, 6},
                                    {7, 8, 9}
                            });

    SymmetricProfileMatrixTest a(denseMatrix);
    expect_equal_matrices(a, denseMatrix);
}


TEST(SymmetricProfileMatrixTests, create_from_dense_02) {
    DenseMatrix denseMatrix({
                                    {1, 0, 0},
                                    {0, 5, 0},
                                    {0, 0, 9}
                            });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> index({0, 0, 0, 0});

    SymmetricProfileMatrixTest a(denseMatrix);
    expect_equal_matrices(a, denseMatrix);

    expect_equal_vectors(a.diagonal, diagonal);
    expect_equal_vectors(a.index, index);
    EXPECT_EQ(a.rowLowerProfile.size(), 0);
    EXPECT_EQ(a.columnUpperProfile.size(), 0);
}


TEST(SymmetricProfileMatrixTests, create_from_dense_03) {
    DenseMatrix denseMatrix({
                                    {1, 0, 1},
                                    {0, 5, 0},
                                    {0, 0, 9}
                            });
    std::vector<double> diagonal({1, 5, 9});
    std::vector<size_t> index({0, 0, 0, 0});

    SymmetricProfileMatrixTest a(denseMatrix);
    expect_equal_matrices(a, denseMatrix);

    expect_equal_vectors(a.diagonal, diagonal);
//    expect_equal_vectors(a.index, index);
//    EXPECT_EQ(a.rowLowerProfile.size(), 0);
//    EXPECT_EQ(a.columnUpperProfile.size(), 0);
}
