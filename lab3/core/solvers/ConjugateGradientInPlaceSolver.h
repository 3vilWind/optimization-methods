#pragma once

#include "Solver.h"

class ConjugateGradientInPlaceSolver : public Solver {
    std::vector<double> solve(Matrix &matrix, std::vector<double> b);
};
