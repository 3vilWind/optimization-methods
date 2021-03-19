#include "Dichotomy.h"

OptimizationMethodDetailedResults
Dichotomy::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    double delta = epsilon / 3;
    result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, 0, right, 0));
    while (right - left > epsilon) {
        double x1 = (left + right - delta) / 2;
        double x2 = (left + right + delta) / 2;
        double y1 = function(x1);
        double y2 = function(x2);
        if (y1 <= y2) {
            right = x2;
        } else {
            left = x1;
        }
        result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, 0, right, 0));
    }
    result.result = (right + left) / 2;

    return result;
}


