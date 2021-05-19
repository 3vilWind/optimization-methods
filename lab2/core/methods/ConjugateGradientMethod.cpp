#include "ConjugateGradientMethod.h"

GradientMethodDetailedResult
ConjugateGradientMethod::minimize(const QuadraticFunction &f, const Vector &start_point, double epsilon) const {
    GradientMethodDetailedResult result;
    result.iterations.push_back(start_point);

    const size_t max_operations = 10000;
    size_t count_operations = 0;
    Vector point = start_point;
    Vector prev_grad = f.gradient(point);
    Vector p = prev_grad.opposite();

    while (prev_grad.norm() > epsilon && count_operations < max_operations) {
        Vector ap = f.a->mulByVector(p);
        double alpha = (prev_grad * prev_grad) / (ap * p);
        point += p * alpha;
        Vector grad = prev_grad + (ap * alpha);
        double beta = 0;
        if (count_operations % point.size() != 0) {
            beta = (grad * grad) / (prev_grad * prev_grad);
        }
        p = grad - (p * beta);
        prev_grad = grad;
        ++count_operations;
        result.iterations.push_back(point);
    }

    result.result = point;
    return result;
}
