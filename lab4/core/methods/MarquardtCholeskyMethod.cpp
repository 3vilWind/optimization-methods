#include <lab3/core/solvers/LUInPlaceSolver.h>
#include "MarquardtCholeskyMethod.h"

HypeOptimizationResult
MarquardtCholeskyMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;
    LUInPlaceSolver solver;

    double tau0 = 100;
    double beta = 0.5;

    Vector x(startPoint);
    result.iterations.push_back(x);
    result.additional.emplace_back();
    (*result.additional.rbegin())["result"] = f.compute(x);
    (*result.additional.rbegin())["tau"] = tau0;
    (*result.additional.rbegin())["cholesky"] = 0;
    double tau;
    Vector g;
    DenseMatrix h;
    while (true) {
        step2:
        g = f.gradient(x);
        h = f.hessian(x);
        tau = tau0;

        step3:
        result.additional.emplace_back();
        (*result.additional.rbegin())["cholesky"] +=1;
        auto kek = h + DenseMatrix::identityMatrix(x.size()) * tau;
        Vector s(solver.solve(kek, (-g).data(), epsilon));

        step4:
        Vector y(x + s);
        double fY = f.compute(y);

        step5:
        if (!isPositiveCholesky(kek)) {
            tau = std::max(tau / beta, 1.0);
            goto step3;
        }

        step6:
        x = y;
        tau0 *= beta;

        result.iterations.push_back(x);

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

bool MarquardtCholeskyMethod::isPositiveCholesky(DenseMatrix& matrix) const {
    int n = matrix.size();

    for (int k = 0; k < n; k++) {
        for (int p = 0; p < k; p++) {
            matrix.set(k, k, matrix.get(k, k) - matrix.get(k, p) * matrix.get(k, p));
        }
        if (matrix.get(k, k) <= 0.0) {
            return false;
        }
        matrix.set(k, k, sqrt(matrix.get(k, k)));
        double r = 1.0 / matrix.get(k, k);
        for (int i = k + 1; i < n; i++) {
            for (int p = 0; p < k; p++) {
                matrix.set(i, k, matrix.get(i, k) - matrix.get(i, p) * matrix.get(k, p));
            }
            matrix.set(i, k, matrix.get(i, k) * r);
            matrix.set(k, i, matrix.get(k, i) * matrix.get(i, k));
        }
    }

    return true;
}
