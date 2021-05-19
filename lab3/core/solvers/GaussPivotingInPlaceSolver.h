#pragma once

#include "Solver.h"


class GaussPivotingInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &matrix, std::vector<double> b) override;
};
