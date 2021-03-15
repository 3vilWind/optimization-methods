#pragma once
#include "../OptimizationMethod.h"

class Brent : public OptimizationMethod {
public:
    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon);
};
