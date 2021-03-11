#pragma once
#include "../OptimizationMethod.h"

class Parabola : public OptimizationMethod{
    virtual OptimizationMethodDetailedResults minimizeDetails(double left, double right, double epsilon);
};
