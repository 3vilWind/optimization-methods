#include <stdexcept>
#include "LUInPlaceSolver.h"


//Doolittle LU Decomposition
std::tuple<LWrapperMatrix, UWrapperMatrix> LUInPlaceSolver::LUDecompose(Matrix &matrix) {
    for (int x = 0, y = 0; x < matrix.size(); y++, x++) {
        for (int j = x; j < matrix.size(); j++) {
            for (int p_x = 0, p_y = 0; p_x < x; p_y++, p_x++) {
                double a = matrix.get(y, p_x), b = matrix.get(p_y, j);
                if (a != 0.0 && b != 0.0) {
                    matrix.set(y, j, matrix.get(y, j) - a * b);
                }
            }
        }

        if (matrix.get(y, x) == 0.0) {
            throw std::runtime_error("error");
        }

        for (int i = x + 1, p_row = y + 1; i < matrix.size(); p_row++, i++) {
            for (int p_x = 0, p_y = 0; p_x < x; p_y++, p_x++) {
                double a = matrix.get(p_row, p_x), b = matrix.get(p_y, x);
                if (a != 0.0 && b != 0.0) {
                    matrix.set(p_row, x, matrix.get(p_row, x) - a * b);
                }
            }
            double c = matrix.get(p_row, x);
            double d = matrix.get(y, x);
            if (c != 0.0 && d != 0.0) {
                matrix.set(p_row, x, c / d);
            }
        }
    }
    return std::make_tuple(LWrapperMatrix(matrix), UWrapperMatrix(matrix));
}

std::vector<double> LUInPlaceSolver::solve(Matrix &a, std::vector<double> b) {
    auto lu = LUDecompose(a);
    LWrapperMatrix l = std::get<0>(lu);
    UWrapperMatrix u = std::get<1>(lu);

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < i; j++) {
            b[i] -= b[j] * l.get(i, j);
        }
    }

    for (int i = a.size() - 1; i >= 0; i--) {
        for (int j = i + 1; j < a.size(); j++) {
            b[i] -= b[j] * u.get(i, j);
        }
        b[i] /= u.get(i, i);
    }

    return b;
}
