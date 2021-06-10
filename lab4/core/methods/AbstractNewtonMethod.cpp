#include "AbstractNewtonMethod.h"

HypeOptimizationResult
AbstractNewtonMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;

    Vector x = init(f, startPoint, epsilon, result);
    result.iterations.push_back(x);

    bool flag = true;
    while (flag) {
        Vector delta = iterationStep(f, x, epsilon, result);
        x += delta;
        result.iterations.push_back(x);

        if (delta.norm() < epsilon)
            flag = false;
    }
    result.result = x;

    return result;
}
