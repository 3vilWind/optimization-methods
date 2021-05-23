#pragma once
#include "../matrices/Matrix.h"
#include <vector>

class Solver {
public:
    virtual std::vector<double> solve(Matrix &a, std::vector<double> b, double epsilon) = 0;
};
