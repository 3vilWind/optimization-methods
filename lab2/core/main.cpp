#include <iostream>
#include "lab1/core/methods/Dichotomy.h"
#include "lab1/core/methods/Fibonacci.h"
#include "lab1/core/methods/GoldenRatio.h"
#include "lab1/core/methods/Parabola.h"
#include "lab1/core/methods/Brent.h"
#include "methods/ConjugateGradientMethod.h"
#include "methods/GradientDescent.h"
#include "methods/GradientSteepestDescent.h"
#include "SquareMatrix.h"
#include "DiagonalMatrix.h"
#include "Matrix.h"
#include "QuadraticFunction.h"


void print_two_dimentional(GradientMethod &method, QuadraticFunction &f, Vector &start_point, double epsilon) {
    GradientMethodDetailedResult result = method.minimize(f, start_point, epsilon);
    for (int i = 0; i < result.iterations.size(); ++i) {
        printf("%d %s\n", i, result.iterations[i].to_string().c_str());
    }
}


void print_diagonal(GradientMethod &method, double epsilon) {
    ConjugateGradientMethod conjugateGradientMethod;
    GradientDescent gradientDescent;
    GradientSteepestDescent gradientSteepestDescent;
    std::vector<size_t> condition = {2, 5, 10, 25, 50, 100, 200, 300};
    for (size_t sz = 10; sz <= 10000; sz *= 10) {
        for (size_t cond : condition) {
            printf("%s %zu %s %zu\n", "n =", sz, "k =", cond);
            double res = 0;
            for (size_t i = 0; i < 10; ++i) {
                DiagonalMatrix a(sz, cond);
                Vector b = Vector::random_vector(sz, 10);
                Vector start_point = Vector(std::vector<double>(sz, 15));
                QuadraticFunction f(&a, &b, 2);
                GradientMethodDetailedResult result = gradientSteepestDescent.minimize(f,
                                                                                       start_point,
                                                                                       epsilon);
                res += result.iterations.size();
                printf("%u \n", result.iterations.size());
            }
            printf("%f\n", res / 10);
        }
    }
}

int main() {
    DiagonalMatrix a(Vector(std::vector<double>({2, 8})));
    Vector b(std::vector<double>({-4, -2}));
    Vector start_point(std::vector<double>({15, 15}));
    const double c = 0;
    const double epsilon = 1e-4;

    QuadraticFunction f(&a, &b, c);

    GradientDescent gradientDescent;
    GradientSteepestDescent gradientSteepestDescent;
    ConjugateGradientMethod conjugateGradientMethod;
    printf("%s\n%s\n", "Двумерная функция", "Метод градиентного спуска");
    print_two_dimentional(gradientDescent, f, start_point, epsilon);
    printf("%s\n", "Метод наискорейшего спуска");
    print_two_dimentional(gradientSteepestDescent, f, start_point, epsilon);
    printf("%s\n", "Метод сопряженных градиентов");
    print_two_dimentional(conjugateGradientMethod, f, start_point, epsilon);
    printf("%s\n%s\n", "Диагональная матрица", "Метод градиентного спуска");
    print_diagonal(gradientDescent, epsilon);
    printf("%s\n", "Метод наискорейшего спуска");
    print_diagonal(gradientSteepestDescent, epsilon);
    printf("%s\n", "Метод сопряженных градиентов");
    print_diagonal(conjugateGradientMethod, epsilon);
    return 0;
}
