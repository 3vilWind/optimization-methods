#include "GradientDescent.h"


GradientMethodDetailedResult
GradientDescent::minimize(const QuadraticFunction &f, const Vector &start_point, double epsilon) const {
    GradientMethodDetailedResult result;
    result.iterations.push_back(start_point);

    double alpha = 2 / f.maxEigenValue;
    size_t max_operations = 10000;
    size_t count_operations = 0;
    Vector point = start_point;
    Vector grad = f.gradient(point);

    while (grad.norm() > epsilon && count_operations < max_operations) {
        Vector next_point = point + (grad * -alpha);
        if (f.evaluate(next_point) >= f.evaluate(point)) {
            alpha /= 2;
        } else {
            point = next_point;
            grad = f.gradient(point);
            ++count_operations;
            result.iterations.push_back(point);
        }
    }

    result.result = point;
    return result;
}
