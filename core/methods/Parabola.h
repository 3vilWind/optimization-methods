#pragma once

#include "../OptimizationMethod.h"

class Parabola : public OptimizationMethod {
public:
    using OptimizationMethod::OptimizationMethod;

    OptimizationMethodDetailedResults minimize(double left, double right, double epsilon) override;

    static void getParabolaCoefficients(double x1, double y1, double x2, double y2, double x3, double y3,
                                        double &a, double &b, double &c);

    static double getParabolaMinimum(double x1, double y1, double x2, double y2, double x3, double y3);
};
