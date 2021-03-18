#include "Parabola.h"
#include "../Utils.h"

OptimizationMethodDetailedResults Parabola::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    double x1 = left;
    double x3 = right;
    double x2 = (left + right) / 2;
    double x_cur = x1, x_prev = x3;
    while (abs(x_cur - x_prev) > epsilon) {
        double y1 = function(x1);
        double y2 = function(x2);
        double y3 = function(x3);
        double a0 = y1;
        double a1 = (y2 - y1) / (x2 - x1);
        double a2 = ((y3 - y1) / (x3 - x1) - (y2 - y1) / (x2 - x1)) / (x3 - x2);
        x_prev = x_cur;
        x_cur = (x1 + x2 - a1 / a2) / 2;
        double y_cur = function(x_cur);
        if (x1 < x_cur && x_cur < x2 && y_cur >= y2) {
            x1 = x_cur;
        } else if (x1 < x_cur && x_cur < x2 && y_cur < y2) {
            shift2(x3, x2, x_cur);
        } else if (x_cur > x2 && x_cur < x3 && y_cur < y2) {
            shift2(x1, x2, x_cur);
        } else if (x_cur > x2 && x_cur < x3 && y_cur > y2) {
            x3 = x_cur;
        }
    }
    result.result = x_cur;
    return result;
}