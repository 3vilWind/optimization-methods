#include "Brent.h"
#include <cmath>

bool isDifferent(double a, double b, double c) {
    return a != b && b != c && a != c;
}

int sgn(double x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

OptimizationMethodDetailedResults Brent::minimize(double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;
    const double CGOLD = (3 - sqrt(5)) / 2;
    double x, w, v, fx, fw, fv, e, g;
    bool fl = false;
    double u = left;
    double d = e = right - left;
    x = w = v = left + CGOLD * (right - left);
    fx = fw = fv = function(x);
    while (right - left > epsilon) {
        g = e;
        e = d;
        double tol = epsilon / 10 + epsilon * abs(x);
        if (abs(x - (left + right) / 2) + (right - left) / 2 <= 2 * tol) {
            break;
        }
        if (isDifferent(x, w, v) && isDifferent(fx, fw, fv)) {
            double a0 = fx;
            double a1 = (fw - fx) / (w - x);
            double a2 = ((fv - fx) / (v - x) - (fw - fx) / (w - x)) / (v - w);
            u = (x + w - a1 / a2) / 2;
            if (u >= left && u <= right && abs(u - x) < g / 2) {
                u = x - sgn(x - (left + right) / 2.0) * tol;
                fl = true;
            }
        }
        if (!fl) {
            if (x < (left + right) / 2) {
                u = x + CGOLD * (right - x);
                e = right - x;
            } else {
                u = x - CGOLD * (x - right);
                e = x - right;
            }
        }

        if (abs(u - x) < tol) {
            u = x + sgn(u - x) * tol;
        }

        d = abs(u - x);
        double fu = function(u);
        if (fu < fx) {
            if (u >= x) {
                left = x;
            } else {
                right = x;
            }
            v = w;
            w = x;
            x = u;
            fv = fw;
            fw = fx;
            fx = fu;
        } else {
            if (u >= x) {
                right = u;
            } else {
                left = u;
            }
            if (fu <= fw || w == x) {
                v = w;
                w = u;
                fv = fw;
                fw = fu;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
            }
        }

    }

    return result;
}
