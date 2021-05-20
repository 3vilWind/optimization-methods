#pragma once

#include "../matrices/DenseMatrix.h"
#include "../solvers/LinearSystem.h"

class DiagonallyDominantGenerator {
public:
    LinearSystem generate();
};