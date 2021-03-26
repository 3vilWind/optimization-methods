#include "Fibonacci.h"
#include "../Utils.h"
#include <vector>

size_t Fibonacci::countOperations(double left, double right, double epsilon) {
    size_t n = 0;
    double min = (right - left) / epsilon;
    while (min > fibonacci[n + 2]) {
        ++n;
        if (fibonacci.size() <= n + 2)
            fibonacci.push_back(fibonacci[fibonacci.size() - 2] + fibonacci[fibonacci.size() - 1]);
    }
    return n;
}

OptimizationMethodDetailedResults Fibonacci::minimize(std::function<double(double)> function, double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result = OptimizationMethodDetailedResults();
    int n = countOperations(left, right, epsilon);

    double x1 = left + fibonacci[n] / fibonacci[n + 2] * (right - left);
    double x2 = left + fibonacci[n + 1] / fibonacci[n + 2] * (right - left);
    double y1 = function(x1);
    double y2 = function(x2);

    result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, right));
    for (int i = 1; i < n + 1; ++i) {
        if (y1 >= y2) {
            left = x1;
            shift2(x1, x2, left + fibonacci[n - i + 1] / fibonacci[n - i + 2] * (right - left));
            shift2(y1, y2, function(x2));
        } else {
            right = x2;
            shift2(x2, x1, left + fibonacci[n - i] / fibonacci[n - i + 2] * (right - left));
            shift2(y2, y1, function(x1));
        }
        result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, right));
    }
    result.result = (left + right) / 2;
    return result;
}
