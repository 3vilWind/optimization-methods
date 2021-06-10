#pragma once

#include "AbstractNewtonMethod.h"

class ClassicNewtonMethod : public AbstractNewtonMethod {
protected:
    Vector init(const ScalarFunction &f, const Vector &startPoint, double epsilon,
                HypeOptimizationResult &result) const override;

    Vector iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon,
                         HypeOptimizationResult &result) const override;
};
