#pragma once

#include "../HypeOptimizationMethod.h"

class BfgshMethod : public HypeOptimizationMethod {
public:
    HypeOptimizationResult minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const override;
};
