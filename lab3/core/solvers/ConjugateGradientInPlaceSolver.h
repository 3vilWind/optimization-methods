#pragma once

#include "Solver.h"

class ConjugateGradientInPlaceSolver : public Solver {
    std::vector<double> solve(Matrix &a, std::vector<double> b);
};
