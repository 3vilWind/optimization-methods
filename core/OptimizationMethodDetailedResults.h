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

    static std::vector<NamedShapePoints> getBorders(double x1, double y1, double x2, double y2);
};