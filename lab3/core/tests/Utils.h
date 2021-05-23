#pragma once

#include <gtest/gtest.h>
#include "../matrices/Matrix.h"


void expectEqualMatrices(const Matrix &a, const Matrix &b);

void expectEqualVectors(const std::vector<double> &a, const std::vector<double> &b, double epsilon = 0);

void expectEqualVectors(const std::vector<size_t> &a, const std::vector<size_t> &b);