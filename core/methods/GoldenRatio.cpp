#include "GoldenRatio.h"
#include "../Utils.h"
#include <cmath>

OptimizationMethodDetailedResults GoldenRatio::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    const double GOLDEN_PHI = (1 + sqrt(5)) / 2;

    double x1 = left + (2 - GOLDEN_PHI) * (right - left);
    double x2 = right - (2 - GOLDEN_PHI) * (right - left);
    double y1 = function(x1);
    double y2 = function(x2);

    result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, 0, right, 0));

    while (right - left > epsilon) {
        if (y1 >= y2) {
            left = x1;
            shift2(x1, x2, right - (2 - GOLDEN_PHI) * (right - left));
            shift2(y1, y2, function(x2));
        } else {
            right = x2;
            shift2(x2, x1, left + (2 - GOLDEN_PHI) * (right - left));
            shift2(y2, y1, function(x1));
        }
        result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, 0, right, 0));
    }
    result.result = (left + right) / 2;

    return result;
}
