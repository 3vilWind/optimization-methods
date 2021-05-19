#pragma once
#include "../matrices/Matrix.h"
#include <vector>

class Solver {
public:
    virtual std::vector<double> solve(Matrix& matrix, std::vector<double> b) = 0;
};
