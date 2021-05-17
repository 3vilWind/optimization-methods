#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>
#include "SquareMatrix.h"
#include "Vector.h"
#include "GradientMethodDetailedResult.h"
#include "QuadraticFunction.h"


class GradientMethod {
public:
    virtual GradientMethodDetailedResult
    minimize(const QuadraticFunction &f, const Vector &start_point, double epsilon) const = 0;

    virtual ~GradientMethod() = default;
};
