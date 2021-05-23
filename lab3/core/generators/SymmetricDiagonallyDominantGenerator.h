#pragma once

#include "../matrices/SymmetricSparseRowColumnMatrix.h"


SymmetricSparseRowColumnMatrix generateSymmetricDiagonallyDominantMatrix(size_t n, bool invertSignOffDiagonal);

DenseMatrix generateSymmetricDiagonallyDominantDenseMatrix(size_t n, bool invertSignOffDiagonal);