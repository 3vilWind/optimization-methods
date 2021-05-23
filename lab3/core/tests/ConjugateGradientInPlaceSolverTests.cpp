#include "../matrices/SparseRowColumnMatrix.h"
#include "../solvers/ConjugateGradientInPlaceSolver.h"
#include <gtest/gtest.h>
#include "Utils.h"

class ConjugateGradientInPlaceSolverTests : public ConjugateGradientInPlaceSolver {
    using ConjugateGradientInPlaceSolver::ConjugateGradientInPlaceSolver;
};


TEST(ConjugateGradientInPlaceSolverTests, solver) {
    DenseMatrix denseMatrix({
                                    {1, 6, 2},
                                    {6, 0, 4},
                                    {2, 4, 3}
                            });
    SparseRowColumnMatrix sparseMatrix(denseMatrix);
    std::vector<double> b = {47, 46, 47};
    std::vector<double> result = {3, 5, 7};

    ConjugateGradientInPlaceSolver solver;
    auto r = solver.solve(sparseMatrix, b, 1e-7);
    expectEqualVectors(r, result, 1e-7);
}
