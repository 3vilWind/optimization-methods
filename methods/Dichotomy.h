#pragma once
#include "../OptimizationMethod.h"

class Dichotomy : public OptimizationMethod {
public:
    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon);
};
