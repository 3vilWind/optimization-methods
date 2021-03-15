#pragma once
#include "../OptimizationMethod.h"

class GoldenRatio : public OptimizationMethod {
    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon);
};
