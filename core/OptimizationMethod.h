#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>
#include "OptimizationMethodDetailedResults.h"

class OptimizationMethod {
public:
    virtual OptimizationMethodDetailedResults
    minimize(std::function<double(double)> function, double left, double right, double epsilon) = 0;
    virtual ~OptimizationMethod() = default;
};
