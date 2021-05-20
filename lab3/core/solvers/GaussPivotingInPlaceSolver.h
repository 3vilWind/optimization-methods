#pragma once

#include "Solver.h"


class GaussPivotingInPlaceSolver : public Solver {
public:
    std::vector<double> solve(LinearSystem system) override;
};
