#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>
#include "OptimizationMethodDetailedResults.h"

class OptimizationMethod {
public:
    std::function<double(double)> function;

    explicit OptimizationMethod(std::function<double(double)> function) : function(std::move(function)) {}

    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon) = 0;

    std::vector<Point> evaluateFunction(double left, double right, double step);
};
