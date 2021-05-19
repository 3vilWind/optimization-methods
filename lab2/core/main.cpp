#include <iostream>

#include "methods/ConjugateGradientMethod.h"
#include "methods/GradientDescent.h"
#include "methods/GradientSteepestDescent.h"
#include "SquareMatrix.h"
#include "DiagonalMatrix.h"
#include "Matrix.h"
#include "QuadraticFunction.h"


void print_two_dimensional(GradientMethod &method, QuadraticFunction &f, Vector &start_point, double epsilon) {
    GradientMethodDetailedResult result = method.minimize(f, start_point, epsilon);
    printf("iteration\tresult\n");
    for (int i = 0; i < result.iterations.size(); ++i) {
        printf("%d\t%s\n", i, result.iterations[i].to_string().c_str());
    }
}


void print_diagonal(GradientMethod &method, double epsilon) {
    ConjugateGradientMethod conjugateGradientMethod;
    GradientDescent gradientDescent;
    GradientSteepestDescent gradientSteepestDescent;
    std::vector<size_t> condition = {2, 5, 10, 25, 50, 100, 200, 300};

    printf("n\tk\titerations\n");
    for (size_t sz = 10; sz <= 10000; sz *= 10) {
        for (size_t cond : condition) {
            printf("%zu\t%zu\t", sz, cond);
            double res = 0;
            for (size_t i = 0; i < 10; ++i) {
                DiagonalMatrix a = DiagonalMatrix::getRandomMatrix(sz, cond);
                Vector b = Vector::getRandomVector(sz, 10);
                Vector start_point = Vector(std::vector<double>(sz, 15));
                QuadraticFunction f(&a, &b, 2);
                GradientMethodDetailedResult result = gradientSteepestDescent.minimize(f,
                                                                                       start_point,
                                                                                       epsilon);
                res += result.iterations.size();
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

    printf("Two dimensional function\n");
    printf("%s\n", "Gradient descent method");
    print_two_dimensional(gradientDescent, f, start_point, epsilon);
    printf("%s\n", "Gradient steepest method");
    print_two_dimensional(gradientSteepestDescent, f, start_point, epsilon);
    printf("%s\n", "Conjugate gradient method");
    print_two_dimensional(conjugateGradientMethod, f, start_point, epsilon);
    printf("\n");

    printf("Diagonal matrix function\n");
    printf("%s\n", "Gradient descent method");
    print_diagonal(gradientDescent, epsilon);
    printf("%s\n", "Gradient steepest method");
    print_diagonal(gradientSteepestDescent, epsilon);
    printf("%s\n", "Conjugate gradient method");
    print_diagonal(conjugateGradientMethod, epsilon);
    return 0;
}
