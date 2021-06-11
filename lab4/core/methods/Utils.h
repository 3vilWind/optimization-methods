#pragma once

#include "lab1/core/OptimizationMethod.h"
#include "../ScalarFunction.h"

double oneDimensionalMinimize(const ScalarFunction &f,
                              const Vector &x,
                              const Vector &d,
                              double epsilon);
