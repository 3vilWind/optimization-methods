#pragma once

#include "../OptimizationMethod.h"

class Fibonacci : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};

