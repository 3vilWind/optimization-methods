#pragma once

#include "include/jacobi_pd.hpp"
#include "SquareMatrix.h"
#include "Vector.h"


class QuadraticFunction {
public:
    const SquareMatrix *a;
    const Vector *b;
    const double c;
    const double maxEigenValue;

    QuadraticFunction(const SquareMatrix *a, const Vector *b, double c) : a(a), b(b), c(c), maxEigenValue(computeMaxEigenValue()) {
    }

    double evaluate(const Vector &x) const {
        return 0.5 * a->vector_multiplication(x).scalar_multiplication(x) + b->scalar_multiplication(x) + c;
    }

    Vector gradient(const Vector &x) const {
        return a->vector_multiplication(x).add(*b);
    }

private:
    double computeMaxEigenValue() const {
        std::vector<std::vector<double>> matrix;
        matrix.reserve(a->number_of_rows());
        for (int i = 0; i < a->number_of_rows(); ++i) {
            matrix.emplace_back(a->row(i).getPlainVector());
        }
        std::vector<double> eigenValues(a->number_of_rows(), 0);
        std::vector<std::vector<double>> eigenVectors(a->number_of_columns(), std::vector<double>(a->number_of_rows(), 0));
        typedef jacobi_pd::Jacobi<double,
                std::vector<double> &,
                std::vector<std::vector<double>> &,
                const std::vector<std::vector<double>> &> Jacobi;
        Jacobi eigenCalc(a->number_of_rows());

        eigenCalc.Diagonalize(matrix, eigenValues, eigenVectors, Jacobi::SORT_DECREASING_EVALS, false);
        return eigenValues[0];
    }
};
