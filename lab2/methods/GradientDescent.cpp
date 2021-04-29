#include "GradientDescent.h"

GradientMethodDetailedResult
GradientDescent::minimize(std::function<double(Vector)> function,
                          std::function<Vector(Vector)> gradient,
                          SquareMatrix &A, double epsilon, Vector start_point, double alpha) {
    GradientMethodDetailedResult result;
    result.iterations.push_back(start_point);
    size_t max_operations = 10000;
    size_t count_operations = 0;
    Vector point = start_point;
    Vector grad = gradient(point);
    while (grad.norm() > epsilon && count_operations < max_operations) {
        Vector next_point = point.add(grad.number_multiplication(-alpha / grad.norm()));
        if (function(next_point) >= function(point)) {
            alpha /= 2;
        } else {
            point = next_point;
            grad = gradient(point);
            ++count_operations;
            result.iterations.push_back(point);
        }
    }
    result.result = point;
    return result;
}
