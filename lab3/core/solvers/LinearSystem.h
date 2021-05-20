#pragma once

#include <vector>
#include "../matrices/Matrix.h"


struct LinearSystem {
    Matrix &a;
    std::vector<double> &b;

    LinearSystem(Matrix &a, std::vector<double> &b) : a(a), b(b) {}
};
