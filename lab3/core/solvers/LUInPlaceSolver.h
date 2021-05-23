#pragma once

#include "../matrices/LUWrapperMatrix.h"
#include "Solver.h"
#include "tuple"

class LUInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &a, std::vector<double> b, double epsilon) override;

protected:
    std::tuple<LWrapperMatrix, UWrapperMatrix> LUDecompose(Matrix &matrix);
};

