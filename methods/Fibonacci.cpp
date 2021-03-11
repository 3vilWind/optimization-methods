#include "Fibonacci.h"
#include <vector>

std::vector<long long> fibonacci = {1, 1, 2};

size_t countOperations (double left, double right, double epsilon) {
    size_t result = 0;
    double min = (right - left) / epsilon;
    while (min < fibonacci[result + 2]) {
        ++result;
        fibonacci.push_back(fibonacci[result] + fibonacci[result + 1]);
    }
    return result;
}
OptimizationMethodDetailedResults Fibonacci::minimizeDetails(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result = OptimizationMethodDetailedResults();
    int numberOfOperations = countOperations(left, right, epsilon);
    size_t count = 0;
    while (count < numberOfOperations) {
        double x1 = left + fibonacci[numberOfOperations - count + 1] / fibonacci[numberOfOperations + 3] * (right - left);
        double x2 = left + fibonacci[numberOfOperations - count + 2] / fibonacci[numberOfOperations + 3] * (right - left);
        double y1 = function(x1);
        double y2 = function(x2);
        if (y1 >= y2) {
            left = x1;
        } else {
            right = x2;
        }
        ++count;
        Point new_left(x1, y1);
        Point new_right(x2, y2);
        result.iterations.push_back({{"left", {new_left}},
                                     {"right", {new_right}}});
    }
    return result;
}
