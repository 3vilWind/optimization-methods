#include "Fibonacci.h"
#include <vector>

size_t Fibonacci::countOperations(double left, double right, double epsilon) {
    size_t result = 0;
    double min = (right - left) / epsilon;
    while (min > fibonacci[result + 2]) {
        ++result;
        fibonacci.push_back(fibonacci[fibonacci.size() - 2] + fibonacci[fibonacci.size() - 1]);
    }
    return result;
}

OptimizationMethodDetailedResults Fibonacci::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result = OptimizationMethodDetailedResults();
    int numberOfOperations = countOperations(left, right, epsilon);
    size_t count = 1;
    while (count < numberOfOperations) {
        double x1 = left + fibonacci[numberOfOperations - count + 1] / fibonacci[numberOfOperations - count + 3] *
                           (right - left);
        double x2 = left + fibonacci[numberOfOperations - count + 2] / fibonacci[numberOfOperations - count + 3] *
                           (right - left);
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
        result.iterations.push_back({{"left",  {new_left}},
                                     {"right", {new_right}}});
    }
    result.result = (left + right) / 2;
    return result;
}
