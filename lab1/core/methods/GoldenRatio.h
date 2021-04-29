#pragma once

#include "../OptimizationMethod.h"

class GoldenRatio : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(std::function<double(double)> function, double left, double right, double epsilon) override;
};
