#include "ConjugateGradientMethod.h"

GradientMethodDetailedResult
ConjugateGradientMethod::minimize(std::function<double(Vector)> function,
                                  std::function<Vector(Vector)> gradient, SquareMatrix &A, double epsilon,
                                  Vector start_point, double alpha) {
    GradientMethodDetailedResult result;
    result.iterations.push_back(start_point);
    const size_t max_operations = 10000;
    size_t count_operations = 0;
    Vector point = start_point;
    Vector prev_grad = gradient(point);
    Vector p = prev_grad.opposite();
    while (prev_grad.norm() > epsilon && count_operations < max_operations) {
        Vector ap = A.vector_multiplication(p);
        alpha = prev_grad.scalar_multiplication(prev_grad) / ap.scalar_multiplication(p);
        point = point.add(p.number_multiplication(alpha));
        Vector grad = prev_grad.add(ap.number_multiplication(alpha));
        double beta = 0;
        if (count_operations % point.size() != 0) {
            beta = (grad.scalar_multiplication(grad)) / (prev_grad.scalar_multiplication(prev_grad));
        }
        p = grad.opposite().add(p.number_multiplication(beta));
        prev_grad = grad;
        ++count_operations;
        result.iterations.push_back(point);
    }
    result.result = point;
    return result;
}
