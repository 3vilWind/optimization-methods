#pragma once
#include <vector>
#include <string>
#include "../matrices/Matrix.h"


std::vector<double> generateB(const Matrix &A, const std::vector<double> &x);

std::vector<double> generateIncrementalVector(size_t n);
