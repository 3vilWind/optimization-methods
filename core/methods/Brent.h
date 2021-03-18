#pragma once

#include "../OptimizationMethod.h"

class Brent : public OptimizationMethod {
public:
    using OptimizationMethod::OptimizationMethod;
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};
