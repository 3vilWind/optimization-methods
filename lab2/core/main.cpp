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


DiagonalMatrix a = DiagonalMatrix(
        Vector(std::vector<double>({48, 126})));
SquareMatrix &A = a;
Vector b = Vector(std::vector<double>({56, -122}));
double c = 2;
Vector start_point = Vector(std::vector<double>({15, 15}));
double epsilon = 1e-4;
double start_alpha = 100;

double function(Vector x) {
    return 0.5 * A.vector_multiplication(x).scalar_multiplication(x) + b.scalar_multiplication(x) + c;
}

Vector gradient(Vector x) {
    return A.vector_multiplication(x).add(b);
}

void print_two_dimentional(GradientMethod &method) {
    GradientMethodDetailedResult result = method.minimize(function, gradient, A, epsilon,
                                                          start_point, start_alpha);
    for (int i = 0; i < result.iterations.size(); ++i) {
        printf("%d %s\n", i, result.iterations[i].to_string().c_str());
    }
}

void print_diagonal(GradientMethod &method) {
    ConjugateGradientMethod conjugateGradientMethod;
    GradientDescent gradientDescent;
    GradientSteepestDescent gradientSteepestDescent;
    std::vector<size_t> condition = {2, 5, 10, 25, 50, 100, 200, 300};
    for (size_t sz = 10; sz <= 10000; sz *= 10) {
        for (size_t cond : condition) {
            printf("%s %zu %s %zu\n", "n =", sz, "k =", cond);
            double res = 0;
            for (size_t i = 0; i < 10; ++i) {
                a = DiagonalMatrix(sz, cond);
                A = a;
                b = Vector::random_vector(sz, 10);
                std::vector<double> start(sz, 15);
                start_point = Vector(start);
                GradientMethodDetailedResult result = gradientSteepestDescent.minimize(function, gradient, A,
                                                                                       epsilon,
                                                                                       start_point, start_alpha);
                res += result.iterations.size();
                printf("%u \n", result.iterations.size());
            }
            printf("%f\n", res / 10);
        }
    }
}

int main() {
    GradientDescent gradientDescent;
    GradientSteepestDescent gradientSteepestDescent;
    ConjugateGradientMethod conjugateGradientMethod;
    printf("%s\n%s\n", "Двумерная функция", "Метод градиентного спуска");
    print_two_dimentional(gradientDescent);
    printf("%s\n", "Метод наискорейшего спуска");
    print_two_dimentional(gradientSteepestDescent);
    printf("%s\n", "Метод сопряженных градиентов");
    print_two_dimentional(conjugateGradientMethod);
    printf("%s\n%s\n", "Диагональная матрица", "Метод градиентного спуска");
    print_diagonal(gradientDescent);
    printf("%s\n", "Метод наискорейшего спуска");
    print_diagonal(gradientSteepestDescent);
    printf("%s\n", "Метод сопряженных градиентов");
    print_diagonal(conjugateGradientMethod);
    return 0;
}
