#include "Dichotomy.h"

OptimizationMethodDetailedResults
Dichotomy::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;

    Point first_left(left, function(left));
    Point first_right(right, function(right));
    result.iterations.push_back({{"left", {first_left}},
                                 {"right", {first_right}}});

    while (right - left > epsilon) {
        double x1 = (left + right - epsilon) / 2;
        double x2 = (left + right + epsilon) / 2;
        double y1 = function(x1);
        double y2 = function(x2);
        if (y1 <= y2) {
            right = x2;
        } else {
            left = x1;
        }
        Point new_left(x1, y1);
        Point new_right(x2, y2);
        result.iterations.push_back({{"left", {new_left}},
                                     {"right", {new_right}}});
    }

    return result;
}


