#include "../matrices/DenseMatrix.h"
#include "../solvers/GaussPivotingInPlaceSolver.h"
#include <gtest/gtest.h>
#include "Utils.h"

class GaussPivotingInPlaceSolverTest : public GaussPivotingInPlaceSolver {
    using GaussPivotingInPlaceSolver::GaussPivotingInPlaceSolver;
};


TEST(GaussPivotingInPlaceSolverTests, solver) {
    DenseMatrix denseMatrix({
                                    {4, 1, 1},
                                    {1, 6, -1},
                                    {1, 2, 5}
                            });
    std::vector<double> b = {9, 10, 20};
    std::vector<double> result = {1, 2, 3};

    GaussPivotingInPlaceSolverTest solver;
    auto r = solver.solve(denseMatrix, b, 0);
    expectEqualVectors(r, result);
}
