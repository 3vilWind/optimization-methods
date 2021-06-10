#include <cstdio>

#include "methods/ClassicNewtonMethod.h"
#include "methods/LinearSearchNewtonMethod.h"
#include "methods/DescentNewtonMethod.h"
#include "ExampleFunctions.h"


int main() {
    F_1_1_1 f;
    ClassicNewtonMethod method;
    HypeOptimizationResult result = method.minimize(f, Vector({4, 1}), 1e-3);

    printf("(%f, %f) with %llu iterations\n", result.result[0], result.result[1], result.iterations.size());

    return 0;
}