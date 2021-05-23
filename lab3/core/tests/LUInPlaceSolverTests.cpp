#include "../matrices/DenseMatrix.h"
#include "../matrices/SymmetricProfileMatrix.h"
#include "../solvers/LUInPlaceSolver.h"
#include <gtest/gtest.h>
#include "Utils.h"

class LUInPlaceSolverTest : public LUInPlaceSolver {
    using LUInPlaceSolver::LUInPlaceSolver;

    FRIEND_TEST(LUInPlaceSolverTests, LUDecomposition);
};


TEST(LUInPlaceSolverTests, LUDecomposition) {
    DenseMatrix denseMatrix({
                                    {4, 1, 1},
                                    {1, 6, -1},
                                    {1, 2, 5}
                            });
    DenseMatrix l({
                          {1,       0,        0},
                          {1.0 / 4, 1,        0},
                          {1.0 / 4, 7.0 / 23, 1}
                  });

    DenseMatrix u({
                          {4, 1,        1},
                          {0, 23.0 / 4, -5.0 / 4},
                          {0, 0,        118.0 / 23}
                  });
    LUInPlaceSolverTest solver;

    auto r = solver.LUDecompose(denseMatrix);

    expectEqualMatrices(std::get<0>(r), l);
    expectEqualMatrices(std::get<1>(r), u);
}


TEST(LUInPlaceSolverTests, solver) {
    DenseMatrix denseMatrix({
                                    {4, 1, 1},
                                    {1, 6, -1},
                                    {1, 2, 5}
                            });
    std::vector<double> b = {9, 10, 20};
    std::vector<double> result = {1, 2, 3};

    LUInPlaceSolverTest solver;
    auto r = solver.solve(denseMatrix, b, 0);
    expectEqualVectors(r, result);
}

TEST(LUInPlaceSolverTests, solverSymmetricProfile) {
    SymmetricProfileMatrix denseMatrix(
            DenseMatrix({
                                {4, 1, 1},
                                {1, 6, -1},
                                {1, 2, 5}
                        }));
    std::vector<double> b = {9, 10, 20};
    std::vector<double> result = {1, 2, 3};

    LUInPlaceSolverTest solver;
    auto r = solver.solve(denseMatrix, b, 0);
    expectEqualVectors(r, result);
}