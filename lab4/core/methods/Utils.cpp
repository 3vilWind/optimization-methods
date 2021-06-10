#include "Utils.h"


double oneDimensionalMinimize(OptimizationMethod& method,
                              const ScalarFunction &f,
                              const Vector &x,
                              const Vector &d,
                              double epsilon) {
    return method.minimize([&d, &x, &f](double lambda) { return f.compute(x + d * lambda); }, 0, 10, epsilon).result;
}