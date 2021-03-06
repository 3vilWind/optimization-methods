#pragma once

#include <utility>
#include <string>
#include <vector>
#include "OptimizationMethodDetailedResults.h"

class OptimizationMethod {
    std::unary_function<double, double> function;
public:
    explicit OptimizationMethod(std::unary_function<double, double> function) : function(function) {}

    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon) = 0;

    std::vector<Point> evaluateFunction(double left, double right, double step);
};
