#pragma once

#include "../GradientMethod.h"

class ConjugateGradientMethod : public GradientMethod {
public:
    GradientMethodDetailedResult minimize(std::function<double(Vector)> function,
                                          std::function<Vector(Vector)> gradient,
                                          SquareMatrix &A, double epsilon, Vector start_point, double alpha) override;

};
