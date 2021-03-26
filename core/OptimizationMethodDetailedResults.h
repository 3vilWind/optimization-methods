#pragma once

#include <vector>
#include <map>
#include <string>


struct OptimizationMethodDetailedResults {
    double result;
    std::vector<std::map<std::string, double>> iterations;

    static std::map<std::string, double> getBorders(double x1, double x2);
};