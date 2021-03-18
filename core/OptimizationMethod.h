#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>
#include "OptimizationMethodDetailedResults.h"

class OptimizationMethod {
protected:
    std::function<double(double)> function;

public:
    explicit OptimizationMethod(std::function<double(double)> function) : function(std::move(function)) {}

    virtual OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) = 0;
};
