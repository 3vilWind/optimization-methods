#pragma once

#include "Solver.h"

using Vector =std::vector<double>;//а чтоб и нет

class ConjugateGradientInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &a, std::vector<double> b, double epsilon) override;
};
