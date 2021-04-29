#include "Utils.h"

void getParabolaCoefficients(double x1, double y1, double x2, double y2, double x3, double y3,
                             double &a, double &b, double &c) {
    double d = ((x1 - x2) * (x1 * x2 - x1 * x3 - x2 * x3 + x3 * x3));
    a = ((y1 - y3) * x2 + (y2 - y1) * x3 + (y3 - y2) * x1) / d;
    b = -((y1 - y3) * x2 * x2 + (y2 - y1) * x3 * x3 + (y3 - y2) * x1 * x1) / d;
    c = -(-(y1 * x3 - y3 * x1) * x2 * x2 - (y2 * x1 - y1 * x2) * x3 * x3 - (y3 * x2 - y2 * x3) * x1 * x1) / d;
}


double getParabolaMinimum(double x1, double y1, double x2, double y2, double x3, double y3) {
    return x2 - ((x2 - x1) * (x2 - x1) * (y2 - y3) - (x2 - x3) * (x2 - x3) * (y2 - y1)) /
                (2 * ((x2 - x1) * (y2 - y3) - (x2 - x3) * (y2 - y1)));
}
