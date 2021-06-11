#pragma once

#include <lab4/core/HypeOptimizationMethod.h>

class MarquardtMethod : public HypeOptimizationMethod {
public:
    HypeOptimizationResult minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const override;
};