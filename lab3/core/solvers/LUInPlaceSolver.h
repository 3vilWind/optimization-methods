#pragma once

#include "../matrices/LUWrapperMatrix.h"
#include "Solver.h"
#include "tuple"

class LUInPlaceSolver : public Solver {
public:
    std::vector<double> solve(LinearSystem system) override;

protected:
    std::tuple<LWrapperMatrix, UWrapperMatrix> LUDecompose(Matrix &matrix);
};

