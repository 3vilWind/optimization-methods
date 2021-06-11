#include "Utils.h"
#include "lab1/core/methods/Brent.h"

double oneDimensionalMinimize(const ScalarFunction &f,
                              const Vector &x,
                              const Vector &d,
                              double epsilon) {
    Brent method;
    return method.minimize([&d, &x, &f](double lambda) { return f.compute(x + d * lambda); }, 0, 10, epsilon).result;
}