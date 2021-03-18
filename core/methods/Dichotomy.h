#pragma once

#include "../OptimizationMethod.h"

class Dichotomy : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};
