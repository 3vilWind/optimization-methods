#include <lab3/core/solvers/LUInPlaceSolver.h>
#include "MarquardtMethod.h"

HypeOptimizationResult
MarquardtMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;
    LUInPlaceSolver solver;

    double alpha0 = 100;
    double beta = 0.5;

    Vector x(startPoint);
    result.iterations.push_back(x);
    result.additional.emplace_back();
    (*result.additional.rbegin())["result"] = f.compute(x);
    double fX = f.compute(x);
    double alpha;
    bool flag = true;
    Vector g;
    DenseMatrix h;
    while (true) {
        if (flag) {
            g = f.gradient(x);
            h = f.hessian(x);
            alpha = alpha0;
        }

        auto kek = h + DenseMatrix::identityMatrix(x.size()) * alpha;
        Vector s(solver.solve(kek, (-g).data(), epsilon));
        Vector y(x + s);
        double fY = f.compute(y);

        if (fY >= fX) {
            alpha/= beta;
            flag = false;
        } else {
            x = y;
            result.additional.emplace_back();
            (*result.additional.rbegin())["result"] = f.compute(x);
            result.iterations.push_back(x);
            fX = fY;
            alpha0 *= beta;
            flag = true;
            if (s.norm() < epsilon) {
                break;
            }
        }
    }
    result.result = x;

    return result;
}
