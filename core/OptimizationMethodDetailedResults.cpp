#include "OptimizationMethodDetailedResults.h"

std::map<std::string, double>
OptimizationMethodDetailedResults::getBorders(double x1, double x2) {
    return std::map<std::string, double>{
            {"left",  x1},
            {"right", x2}
    };
}

