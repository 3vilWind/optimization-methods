#pragma once

#include "Solver.h"

class LUInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &matrix, std::vector<double> b) override;

private:
    void LUDecompose(Matrix &matrix);

    class LUWrapperMatrix {
        Matrix &matrix;
    public:
        explicit LUWrapperMatrix(Matrix &matrix) : matrix(matrix) {}

        double getL(size_t x, size_t y);

        double getU(size_t x, size_t y);
    };
};

