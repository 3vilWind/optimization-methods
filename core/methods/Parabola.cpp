#include "Parabola.h"
#include "../Utils.h"

OptimizationMethodDetailedResults Parabola::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    double x1 = left;
    double x2 = (left + right) / 2;
    double x3 = right;
    double y1 = function(x1), y2 = function(x2), y3 = function(x3);
    result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, 0, right, 0));
    while (abs(x3 - x1) > epsilon) {
        double a, b, c;
        getParabolaCoefficients(x1, y1, x2, y2, x3, y3, a, b, c);
        double xMin = getParabolaMinimum(x1, y1, x2, y2, x3, y3);
        double yMin = function(xMin);

        if (xMin >= x2) {
            if (yMin >= y2) {
                x3 = xMin;
                y3 = yMin;
            } else {
                shift2(x1, x2, xMin);
                shift2(y1, y2, yMin);
            }
        } else {
            if (yMin >= y2) {
                x1 = xMin;
                y1 = yMin;
            } else {
                shift2(x3, x2, xMin);
                shift2(y3, y2, yMin);
            }
        }
        result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(x1, xMin, x3, yMin));
    }
    result.result = x2;
    return result;
}

void Parabola::getParabolaCoefficients(double x1, double y1, double x2, double y2, double x3, double y3,
                                       double &a, double &b, double &c) {
    a = (x2 * y1 - x3 * y1 - x1 * y2 + x3 * y2 + x1 * y3 - x2 * y3) / ((x2 - x1) * (x2 - x3) * (x3 - x1));
    b = (x2 * x2 * y1 - x3 * x3 * y1 - x1 * x1 * y2 + x1 * x1 * y3 - x2 * x2 * y3) /
        ((x2 - x1) * (x1 - x3) * (x2 - x3));
    c = (-x2 * x2 * x3 * y1 + x2 * x3 * x3 * y1 + x1 * x1 * x3 * y2 - x1 * x3 * x3 * y2 - x1 * x1 * x2 * y3 +
         x1 * x2 * x2 * y3) / ((x3 - x2) * (x1 * x1 - x1 * x2 - x1 * x3 + x2 * x3));
}

double Parabola::getParabolaMinimum(double x1, double y1, double x2, double y2, double x3, double y3) {
    return x2 - ((x2 - x1) * (x2 - x1) * (y2 - y3) - (x2 - x3) * (x2 - x3) * (y2 - y1)) /
                (2 * ((x2 - x1) * (y2 - y3) - (x2 - x3) * (y2 - y1)));
}
