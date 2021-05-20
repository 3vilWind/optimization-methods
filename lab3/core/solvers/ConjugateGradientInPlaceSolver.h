#pragma once

#include "Solver.h"
#include "LinearSystem.h"

class ConjugateGradientInPlaceSolver : public Solver {
    std::vector<double> solve(LinearSystem system);
};
