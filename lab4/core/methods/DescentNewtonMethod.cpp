#include "DescentNewtonMethod.h"
#include "lab3/core/solvers/LUInPlaceSolver.h"
#include "lab1/core/methods/Brent.h"
#include "Utils.h"


Vector DescentNewtonMethod::init(const ScalarFunction &f, const Vector &startPoint, double epsilon, HypeOptimizationResult& result) const {
    Brent linearSearch;

    auto d = -f.gradient(startPoint);
    auto r = oneDimensionalMinimize(linearSearch, f, startPoint, d, epsilon);
    result.additional.push_back({{"foundParameter", std::to_string(r)}});
    Vector s(r * d);
    return startPoint + s;
}

Vector DescentNewtonMethod::iterationStep(const ScalarFunction &f, const Vector &prevPoint, double epsilon, HypeOptimizationResult& result) const {
    Brent linearSearch;
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

    double r = oneDimensionalMinimize(linearSearch, f, prevPoint, d, epsilon);
    result.additional.push_back({{"foundParameter", std::to_string(r)}});
    return d * r;
}
