#include <iostream>
#include "methods/Dichotomy.h"
#include "methods/Fibonacci.h"
#include "methods/GoldenRatio.h"
#include "methods/Parabola.h"
#include "methods/Brent.h"

#define M_PI           3.14159265358979323846

double functionVar8(double x) {
    return -3 * x * sin(0.75 * x) + exp(-2 * x);
}


void printTable1(OptimizationMethodDetailedResults &results) {
    double prevLength = 2 * M_PI;
    for (int i = 0; i < results.iterations.size(); ++i) {
        double curLength = results.iterations[i][1].points[0].x - results.iterations[i][0].points[0].x;
        printf("%d %.5f %.5f %.5f %.5f %.5f\n", i,
               results.iterations[i][0].points[0].x,
               functionVar8(results.iterations[i][0].points[0].x),
               results.iterations[i][1].points[0].x,
               functionVar8(results.iterations[i][1].points[0].x),
               prevLength / curLength);
        prevLength = curLength;
    }
}

void printTableParabola(OptimizationMethodDetailedResults &results) {
    double prevLength = 2 * M_PI;
    for (int i = 0; i < results.iterations.size(); ++i) {
        double curLength = results.iterations[i][1].points[0].x - results.iterations[i][0].points[0].x;
        printf("%d %.5f %.5f %.5f %.5f %.5f\n", i,
               results.iterations[i][0].points[0].x,
               results.iterations[i][1].points[0].x,
               prevLength / curLength,
               results.iterations[i][0].points[0].y,
               results.iterations[i][1].points[0].y
        );
        prevLength = curLength;
    }
}

double xsinx(double x) {
    return x * sin(x);
}

double poly(double x) {
    return 6 * pow(x, 4) - 15 * pow(x, 3) - 2 * pow(x, 2) + 13 * x + 10;
}

void printMultiModal() {
    int counter = 0;
    auto counterFunction = [&](double x) {
        counter++;
        return poly(x);
    };

    Dichotomy dichotomy(counterFunction);
    GoldenRatio goldenRatio(counterFunction);
    Fibonacci fibonacci(counterFunction);
    Parabola parabola(counterFunction);
    Brent brent(counterFunction);
    OptimizationMethodDetailedResults resultsDichotomy = dichotomy.minimize(-2, 2, 1e-10);
    int dichotomyCalls = counter;
    counter = 0;
    OptimizationMethodDetailedResults resultsGoldenRatio = goldenRatio.minimize(-2, 2, 1e-10);
    int goldenRatioCalls = counter;
    counter = 0;
    OptimizationMethodDetailedResults resultsFibonacci = fibonacci.minimize(-2, 2, 1e-10);
    int fibonacciCalls = counter;
    counter = 0;
    OptimizationMethodDetailedResults resultsParabola = parabola.minimize(-2, 2, 1e-10);
    int parabolaCalls = counter;
    counter = 0;
    OptimizationMethodDetailedResults resultsBrent = brent.minimize(-2, 2, 1e-10);
    int brentCalls = counter;
    counter = 0;

    printf("%f %f %f %f %f\n",
           resultsDichotomy.result,
           resultsGoldenRatio.result,
           resultsFibonacci.result,
           resultsParabola.result,
           resultsBrent.result);
    printf("%d %d %d %d %d\n", dichotomyCalls, goldenRatioCalls, fibonacciCalls, parabolaCalls, brentCalls);
}

void printComparisonTable() {
    printf("Comparison Table\n");
    for (int i = 3; i < 16; ++i) {
        double epsilon = pow(0.1, i);
        int counter = 0;
        auto counterFunction = [&](double x) {
            counter++;
            return functionVar8(x);
        };
        Dichotomy dichotomy(counterFunction);
        dichotomy.minimize(0, 2 * M_PI, epsilon);
        int dichotomyCalls = counter;
        counter = 0;
        GoldenRatio goldenRatio(counterFunction);
        goldenRatio.minimize(0, 2 * M_PI, epsilon);
        int goldenRatioCalls = counter;
        counter = 0;
        Fibonacci fibonacci(counterFunction);
        fibonacci.minimize(0, 2 * M_PI, epsilon);
        int fibonacciCalls = counter;
        counter = 0;
        Parabola parabola(counterFunction);
        parabola.minimize(0, 2 * M_PI, epsilon);
        int parabolaCalls = counter;
        counter = 0;
        Brent brent(counterFunction);
        brent.minimize(0, 2 * M_PI, epsilon);
        int brentCalls = counter;
        counter = 0;

        printf("%d %d %d %d %d %d\n", i, dichotomyCalls, goldenRatioCalls, fibonacciCalls, parabolaCalls, brentCalls);
    }
}


void printMethodTables() {
    Dichotomy dichotomy(functionVar8);
    GoldenRatio goldenRatio(functionVar8);
    Fibonacci fibonacci(functionVar8);
    Parabola parabola(functionVar8);
    Brent brent(functionVar8);
    OptimizationMethodDetailedResults resultsDichotomy = dichotomy.minimize(0, 2 * M_PI, 0.001);
    OptimizationMethodDetailedResults resultsGoldenRatio = goldenRatio.minimize(0, 2 * M_PI, 0.001);
    OptimizationMethodDetailedResults resultsFibonacci = fibonacci.minimize(0, 2 * M_PI, 0.001);
    OptimizationMethodDetailedResults resultsParabola = parabola.minimize(0, 2 * M_PI, 0.001);
    OptimizationMethodDetailedResults resultsBrent = brent.minimize(0, 2 * M_PI, 0.001);

    printf("Dichotomy\n");
    printTable1(resultsDichotomy);
    printf("Golden Ratio\n");
    printTable1(resultsGoldenRatio);
    printf("Fibonacci\n");
    printTable1(resultsFibonacci);
    printf("Parabola\n");
    printTableParabola(resultsParabola);
    printf("Brent\n");
    printTableParabola(resultsBrent);
}

int main() {
    printMethodTables();
    printComparisonTable();
    printMultiModal();

    return 0;
}
