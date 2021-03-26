#pragma once

#include "../OptimizationMethod.h"

class Brent : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(std::function<double(double)> function, double left, double right, double epsilon) override;
};
