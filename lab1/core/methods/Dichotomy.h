#pragma once

#include "../OptimizationMethod.h"

class Dichotomy : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults
    minimize(std::function<double(double)> function, double left, double right, double epsilon) override;
};
