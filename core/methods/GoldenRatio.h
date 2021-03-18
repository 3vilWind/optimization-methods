#pragma once

#include "../OptimizationMethod.h"

class GoldenRatio : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};
