#pragma once

#include "Solver.h"


class GaussPivotingInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &a, std::vector<double> b) override;
};
