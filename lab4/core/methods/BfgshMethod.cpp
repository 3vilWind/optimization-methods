#include <lab3/core/solvers/LUInPlaceSolver.h>
#include "BfgshMethod.h"
#include "Utils.h"


HypeOptimizationResult BfgshMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    LUInPlaceSolver solver;
    HypeOptimizationResult result;

    Vector x(startPoint);

    Vector gX = f.gradient(x);
    Vector d = -gX;
    DenseMatrix h = DenseMatrix::identityMatrix(x.size());
    result.iterations.push_back(x);
    while (true) {
        double r = oneDimensionalMinimize(f, x, d, epsilon);
        Vector s = d * r;

        x += s;
        Vector gY = gX;
        gX = f.gradient(x);
        Vector p = gX - gY;
        Vector v(h.multiply(s.data()));

        DenseMatrix plusH(p.multiply(p));
        DenseMatrix minusH(v.multiply(v));

        h += plusH * (1.0 / (p * s));
        h -= minusH * (1.0 / (v * s));

        d = Vector(solver.solve(h, (-gX).data(), epsilon));

        result.iterations.push_back(x);

        if (s.norm() < epsilon)
            break;
    }
    result.result = x;

    return result;
}
