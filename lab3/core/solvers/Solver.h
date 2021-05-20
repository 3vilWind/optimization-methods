#pragma once
#include "../matrices/Matrix.h"
#include "LinearSystem.h"
#include <vector>

class Solver {
public:
    virtual std::vector<double> solve(LinearSystem system) = 0;
};
