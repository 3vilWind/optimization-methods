#include "GoldenRatio.h"
#include <math.h>

OptimizationMethodDetailedResults GoldenRatio::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    const double GOLDEN_PHI = (1 + sqrt(5)) / 2;

    Point first_left(left,  function(left));
    Point first_right(right, function(right));
    result.iterations.push_back({{"left", {first_left}},
                                 {"right", {first_right}}});

    while (right - left > epsilon) {
        double dist = (right - left) / GOLDEN_PHI;
        double x1 = right - dist;
        double x2 = left + dist;
        double y1 = function(x1);
        double y2 = function(x2);
        if (y1 >= y2) {
            left = x1;
        } else {
            right = x2;
        }
        Point new_left(x1, y1);
        Point new_right(x2, y2);
        result.iterations.push_back({{"left", {new_left}},
                                     {"right", {new_right}}});
    }

    return result;
}
