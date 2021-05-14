#include "GradientSteepestDescent.h"
#include "lab1/core/methods/Brent.h"

GradientMethodDetailedResult
GradientSteepestDescent::minimize(std::function<double(Vector)> function,
                                  std::function<Vector(Vector)> gradient, SquareMatrix &A, double epsilon,
                                  Vector start_point,
                                  double alpha) {
    GradientMethodDetailedResult result;
    result.iterations.push_back(start_point);
    size_t max_operations = 10000;
    size_t count_operations = 0;
    double max_alpha = 1000;
    Vector point = start_point;
    Vector prev_point = point;
    Vector grad = gradient(point);
    while (gradient(point).norm() > epsilon &&
           (count_operations == 0 || abs(function(prev_point) - function(point)) > epsilon * 0.01) &&
           count_operations < max_operations) {
        auto const find_alpha{
                [point, function, grad](double x) {
                    return function(Vector::add(point, Vector::number_multiplication(grad, -x)));
                }
        };
        prev_point = point;
        Brent brent;
        alpha = brent.minimize(find_alpha, 0, max_alpha, 1e-5).result;
        point = point.add(grad.number_multiplication(-alpha));
        grad = gradient(point);
        ++count_operations;
        result.iterations.push_back(point);
    }
    result.result = point;
    return result;
}
