#include <lab3/core/solvers/LUInPlaceSolver.h>
#include "MarquardtMethod.h"

HypeOptimizationResult
MarquardtMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;
    LUInPlaceSolver solver;

    double tau0 = 100;
    double beta = 0.5;

    Vector x(startPoint);
    result.iterations.push_back(x);
    result.additional.emplace_back();
    (*result.additional.rbegin())["result"] = f.compute(x);
    (*result.additional.rbegin())["tau"] = tau0;
    double fX = f.compute(x);
    double tau;
    Vector g;
    DenseMatrix h;
    while (true) {
        step2:
        g = f.gradient(x);
        h = f.hessian(x);
        tau = tau0;

        step3:
        auto kek = h + DenseMatrix::identityMatrix(x.size()) * tau;
        Vector s(solver.solve(kek, (-g).data(), epsilon));

        step4:
        Vector y(x + s);
        double fY = f.compute(y);

        step5:
        if (fY >= fX) {
            tau /= beta;
            goto step3;
        }

        step6:
        x = y;
        fX = fY;
        tau0 *= beta;

        result.iterations.push_back(x);
        result.additional.emplace_back();
        (*result.additional.rbegin())["tau"] = tau;
        (*result.additional.rbegin())["result"] = f.compute(x);

        step7:
        if (s.norm() < epsilon) {
            break;
        }
        goto step2;
    }
    result.result = x;

    return result;
}
