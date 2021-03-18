#pragma once

#include "../OptimizationMethod.h"

class Parabola : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};
