#include "ClassicNewtonMethod.h"
#include "lab3/core/solvers/LUInPlaceSolver.h"


Vector ClassicNewtonMethod::init(const ScalarFunction &f, const Vector &startPoint, double epsilon,
                                 HypeOptimizationResult &result) const {
    return startPoint;
}

Vector ClassicNewtonMethod::iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon,
                                          HypeOptimizationResult &result) const {
    LUInPlaceSolver solver;

    auto g = f.gradient(prevPoint);
    auto h = f.hessian(prevPoint);
    return Vector(solver.solve(h, (-g).data(), epsilon));
}
