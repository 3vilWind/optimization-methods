#pragma once

#include "../matrices/DenseMatrix.h"

class DiagonallyDominantGenerator {
public:
    std::tuple<DenseMatrix, std::vector<double>> generate(size_t n, size_t k);
};