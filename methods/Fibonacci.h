#pragma once
#include "../OptimizationMethod.h"

class Fibonacci : public OptimizationMethod {
public:
    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon);
};

