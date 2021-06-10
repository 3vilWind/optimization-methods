#include "AbstractNewtonMethod.h"

HypeOptimizationResult
AbstractNewtonMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;
    result.additional.emplace_back();
    Vector x = init(f, startPoint, epsilon, result);
    result.iterations.push_back(x);
    (*result.additional.rbegin())["result"] = f.compute(x);

    bool flag = true;
    while (flag) {
        result.additional.emplace_back();
        Vector delta = iterationStep(f, x, epsilon, result);
        x += delta;
        result.iterations.push_back(x);
        (*result.additional.rbegin())["result"] = f.compute(x);

        if (delta.norm() < epsilon)
            flag = false;
    }
    result.result = x;

    return result;
}
