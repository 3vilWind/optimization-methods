#include "PowellMethod.h"
#include "Utils.h"

HypeOptimizationResult PowellMethod::minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const {
    HypeOptimizationResult result;

    Vector x(startPoint);
    Vector gX = f.gradient(x);
    Vector d = -gX;
    DenseMatrix g = DenseMatrix::identityMatrix(x.size());
    result.iterations.push_back(x);
    result.additional.emplace_back();
    (*result.additional.rbegin())["result"] = f.compute(x);

    while (true) {
        double r = oneDimensionalMinimize(f, x, d, epsilon);
        Vector s = d * r;
        x += s;
        Vector gY = gX;

        gX = f.gradient(x);
        Vector p = gX - gY;
        Vector u = s - Vector(g.multiply(p.data()));
        g += DenseMatrix(u.multiply(u)) * (1.0 / (u * p));
        d = -Vector(g.multiply(gX.data()));

        result.additional.emplace_back();
        (*result.additional.rbegin())["result"] = f.compute(x);
        result.iterations.push_back(x);

        if (s.norm() < epsilon)
            break;
    }
    result.result = x;

    return result;
}
