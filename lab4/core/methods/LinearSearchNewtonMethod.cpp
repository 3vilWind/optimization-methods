#include "LinearSearchNewtonMethod.h"
#include "lab3/core/solvers/LUInPlaceSolver.h"
#include "lab1/core/methods/Brent.h"
#include "Utils.h"


Vector LinearSearchNewtonMethod::init(const ScalarFunction &f, const Vector &startPoint, double epsilon, HypeOptimizationResult& result) const {
    (*result.additional.rbegin())["foundParameter"] =  0.0;
    return startPoint;
}

Vector LinearSearchNewtonMethod::iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon,
                                               HypeOptimizationResult &result) const {
    LUInPlaceSolver solver;

    auto g = f.gradient(prevPoint);
    auto h = f.hessian(prevPoint);
    Vector d(solver.solve(h, (-g).data(), epsilon));

    auto r = oneDimensionalMinimize(f, prevPoint, d, epsilon);
    (*result.additional.rbegin())["foundParameter"] =  r;
    return d * r;
}
