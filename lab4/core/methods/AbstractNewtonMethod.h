#pragma once

#include <tuple>
#include "../HypeOptimizationMethod.h"


class AbstractNewtonMethod : public HypeOptimizationMethod {
public:
    HypeOptimizationResult minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const override;

protected:
    virtual Vector init(const ScalarFunction &f, const Vector& startPoint, double epsilon, HypeOptimizationResult& result) const = 0;
    virtual Vector iterationStep(const ScalarFunction &f, const Vector& prevPoint, double epsilon, HypeOptimizationResult& result) const = 0;
};
