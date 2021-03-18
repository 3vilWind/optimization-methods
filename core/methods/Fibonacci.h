#pragma once

#include "../OptimizationMethod.h"

class Fibonacci : public OptimizationMethod {
private:
    std::vector<double> fibonacci = {1, 1, 2};

    size_t countOperations (double left, double right, double epsilon);
public:
    using OptimizationMethod::OptimizationMethod;
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};

