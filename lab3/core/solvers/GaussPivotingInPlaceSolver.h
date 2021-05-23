#pragma once

#include "Solver.h"


class GaussPivotingInPlaceSolver : public Solver {
public:
    std::vector<double> solve(Matrix &a, std::vector<double> b, double epsilon) override;

protected:
    void static subtract_rows(Matrix &a, size_t row1, size_t row2, size_t from, size_t to, double value);

    std::vector<double> static reverse_gauss(Matrix &a, std::vector<double> &b);
};
