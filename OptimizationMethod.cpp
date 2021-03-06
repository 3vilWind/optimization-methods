#include "OptimizationMethod.h"

std::vector<Point> OptimizationMethod::evaluateFunction(double left, double right, double step) {
    std::vector<Point> result;

    double current = left;
    while (current <= right) {
        current += step;
        result.emplace_back(current, function(current));
    }
    return result;
}
