#include "DescentNewtonMethod.h"
#include "lab3/core/solvers/LUInPlaceSolver.h"
#include "Utils.h"


Vector DescentNewtonMethod::init(const ScalarFunction &f, const Vector &startPoint, double epsilon,
                                 HypeOptimizationResult &result) const {
    result.iterations.push_back(startPoint);
    (*result.additional.rbegin())["result"] = f.compute(startPoint);
    (*result.additional.rbegin())["foundParameter"] =  0;
    auto d = -f.gradient(startPoint);
    auto r = oneDimensionalMinimize(f, startPoint, d, epsilon);
    result.additional.emplace_back();
    (*result.additional.rbegin())["foundParameter"] =  r;
    Vector s(r * d);
    return startPoint + s;
}

Vector DescentNewtonMethod::iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon,
                                          HypeOptimizationResult &result) const {
    LUInPlaceSolver solver;

    auto g = f.gradient(prevPoint);
    auto h = f.hessian(prevPoint);
    Vector s(solver.solve(h, (-g).data(), epsilon));
    Vector d;

    if (s * g < 0) {
        d = s;
    } else {
        d = -g;
    }

    double r = oneDimensionalMinimize(f, prevPoint, d, epsilon);
    (*result.additional.rbegin())["foundParameter"] =  r;
    return d * r;
}
