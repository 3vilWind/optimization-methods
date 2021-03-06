#include "OptimizationMethod.h"

std::vector<Point> OptimizationMethod::evaluateFunction(double left, double right, double step) {
    std::vector<Point> result;

    double current = left;
    while (current <= right) {
        result.emplace_back(current, function(current));
        current += step;
    }
    return result;
}
