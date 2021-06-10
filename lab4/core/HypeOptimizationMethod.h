#pragma once

#include <vector>
#include <map>
#include <string>
#include "ScalarFunction.h"
#include "lab2/core/Vector.h"


struct HypeOptimizationResult {
    Vector result;
    std::vector <Vector> iterations;
    std::vector <std::map<std::string, double>> additional;
};


class HypeOptimizationMethod {
public:
    virtual HypeOptimizationResult minimize(const ScalarFunction &f, const Vector& startPoint, double epsilon) const = 0;
    virtual ~HypeOptimizationMethod() = default;
};
