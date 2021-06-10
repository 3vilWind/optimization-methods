#include "LinearSearchNewtonMethod.h"
#include "lab3/core/solvers/LUInPlaceSolver.h"
#include "lab1/core/methods/Brent.h"
#include "Utils.h"


Vector LinearSearchNewtonMethod::init(const ScalarFunction &f, const Vector &startPoint, double epsilon,
                                      HypeOptimizationResult &result) const {
    result.additional.push_back({{"foundParameter", std::to_string(0.0)}});
    return startPoint;
}

Vector LinearSearchNewtonMethod::iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon,
                                               HypeOptimizationResult &result) const {
    Brent linearSearch;
    LUInPlaceSolver solver;

    auto g = f.gradient(prevPoint);
    auto h = f.hessian(prevPoint);
    Vector d(solver.solve(h, (-g).data(), epsilon));

    auto r = oneDimensionalMinimize(linearSearch, f, prevPoint, d, epsilon);
    result.additional.push_back({{"foundParameter", std::to_string(r)}});
    return d * r;
}
