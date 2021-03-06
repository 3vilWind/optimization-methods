#pragma once

#include <vector>
#include <string>
#include "Point.h"


struct OptimizationMethodDetailedResults {
    struct NamedShapePoints {
        std::string name;
        std::vector<Point> points;
    };

    double result;
    std::vector<std::vector<NamedShapePoints>> iterations;
};