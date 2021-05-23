#pragma once

#include <vector>


std::vector<double> subtract(std::vector<double> a, const std::vector<double> &b);

std::vector<double> sum(std::vector<double> a, const std::vector<double> &b);

double scalar_product(const std::vector<double> &a, const std::vector<double> &b);

double norm(const std::vector<double> &a);

std::vector<double> multiply(std::vector<double> v, double x);