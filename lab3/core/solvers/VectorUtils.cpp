#pragma once

#include <vector>


std::vector<double> subtract(std::vector<double> a, const std::vector<double> &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] -= b[i];
    }
    return a;
}

std::vector<double> sum(std::vector<double> a, const std::vector<double> &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] += b[i];
    }
    return a;
}

double scalar_product(const std::vector<double> &a, const std::vector<double> &b) {
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

double norm(const std::vector<double> &a) {
    return sqrt(scalar_product(a, a));
}

std::vector<double> multiply(std::vector<double> v, double x) {
    for (double &i : v) {
        i *= x;
    }
    return v;
}
