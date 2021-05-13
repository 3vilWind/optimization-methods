#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>
#include "SquareMatrix.h"
#include "Vector.h"
#include "GradientMethodDetailedResult.h"

class GradientMethod {
public:
    virtual GradientMethodDetailedResult
    minimize(std::function<double(Vector)>,
             std::function<Vector(Vector)>,
             SquareMatrix &A, double epsilon, Vector start_point, double alpha) = 0;

    virtual ~GradientMethod() = default;
};
