#include <cstdio>

#include "methods/ClassicNewtonMethod.h"
#include "methods/LinearSearchNewtonMethod.h"
#include "methods/DescentNewtonMethod.h"
#include "methods/BfgshMethod.h"
#include "methods/PowellMethod.h"
#include "methods/MarquardtMethod.h"
#include "methods/MarquardtCholeskyMethod.h"
#include "ExampleFunctions.h"


void p2() {
    std::vector<HypeOptimizationMethod *> methods;
    std::vector<Vector> startPoints{
            Vector({1, 1, 1, 1}),
            Vector({5, 4, 3, 2}),
            Vector({10, 10, 10, 10}),
    };
    methods.emplace_back(new BfgshMethod());
    methods.emplace_back(new PowellMethod());
    methods.emplace_back(new DescentNewtonMethod());

    F_2_3 f;
    printf("\t\t%s\t%s\t%s\n", startPoints[0].to_string().c_str(), startPoints[1].to_string().c_str(), startPoints[2].to_string().c_str());
    for (int i = 0; i < methods.size(); ++i) {
        std::string methodName;
        if (i == 0)
            methodName = "BFGSH";
        else if (i == 1)
            methodName = "Powell";
        else if (i == 2)
            methodName = "Newton";
        printf("%s\t", methodName.c_str());
        for (auto & startPoint : startPoints) {
            HypeOptimizationResult result = methods[i]->minimize(f, startPoint, 1e-7);
            printf("%llu\t", result.iterations.size());
        }
        printf("\n");
    }
}

void p3() {
    Rosenbrock100 f;
    std::vector<HypeOptimizationMethod*> methods;
    methods.emplace_back(new MarquardtMethod());
    methods.emplace_back(new MarquardtCholeskyMethod());
    Vector startPoint(std::vector<double>(100, -1));

    for (int i = 1; i < methods.size(); ++i) {
        if (i == 0)
            printf("Marquardt\n");
        else if (i == 1)
            printf("Marquardt Cholesky\n");
        HypeOptimizationResult result = methods[i]->minimize(f, startPoint, 1e-7);
//        printf("%s\n", result.result.to_string().c_str());
//        printf("%llu\n", result.iterations.size());

        for (int j = 0; j < result.iterations.size(); ++j) {
            printf("%d\t%e\n", j + 1, result.additional[j]["tau"]);
        }

        if (i == 1) {
            printf("Cholesky\n");
            for (int j = 0; j < result.iterations.size(); ++j) {
                printf("%d\t%e\n", j + 1, result.additional[j]["cholesky"]);
            }
        }
    }
}


int main() {
    p3();

    return 0;
}