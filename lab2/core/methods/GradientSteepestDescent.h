#pragma once

#include "../GradientMethod.h"

class GradientSteepestDescent : public GradientMethod {
public:
    GradientMethodDetailedResult
    minimize(const QuadraticFunction &f, const Vector &start_point, double epsilon) const override;
};
