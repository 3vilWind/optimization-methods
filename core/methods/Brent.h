#pragma once

#include "../OptimizationMethod.h"

class Brent : public OptimizationMethod {
public:
    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;
};
