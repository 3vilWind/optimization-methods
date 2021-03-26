#include "Brent.h"
#include "../Utils.h"
#include <cmath>


OptimizationMethodDetailedResults
Brent::minimize(std::function<double(double)> function, double left, double right, double epsilon) {
    OptimizationMethodDetailedResults result;

    const double CGOLD = (3 - sqrt(5)) / 2;
    double d = 0.0, e = 0.0, fu, fv, fw, fx;
    double p, q, r, tol1, tol2, u, v, w, x, xMiddle;
    x = w = v = right;
    fw = fv = fx = function(x);
    result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, right));
    while (true) {
        bool parabolaAccepted = false;
        double a, b, c;
        xMiddle = (left + right) / 2;
        tol1 = epsilon * abs(x);
        tol2 = 2 * tol1;
        if (abs(x - xMiddle) <= (tol2 - (right - left) / 2)) {
            break;
        }

        if (abs(e) > tol1) {
            r = (x - w) * (fx - fv);
            q = (x - v) * (fx - fw);
            p = (x - v) * q - (x - w) * r;
            q = 2 * (q - r);
            if (q > 0)
                p = -p;

            q = abs(q);
            double tmp = e;
            e = d;
            if (abs(p) >= abs(0.5 * q * tmp) || p <= q * (left - x) || p >= q * (right - x))
                //golden ratio
                d = CGOLD * (e = (x >= xMiddle ? left - x : right - x));
            else {
                //parabola
                d = p / q;
                u = x + d;
                if (u - left < tol2 || right - u < tol2)
                    d = SIGN(tol1, xMiddle - x);
                parabolaAccepted = true;
                getParabolaCoefficients(w, fw, x, fx, v, fv, a, b, c);
            }
        } else {
            //golden ratio
            d = CGOLD * (e = (x >= xMiddle ? left - x : right - x));
        }
        u = (abs(d) >= tol1 ? x + d : x + SIGN(tol1, d));
        fu = function(u);
        if (fu <= fx) {
            if (u >= x)
                left = x;
            else
                right = x;
            shift3(v, w, x, u);
            shift3(fv, fw, fx, fu);
        } else {
            if (u < x)
                left = u;
            else
                right = u;
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
        result.iterations.push_back(OptimizationMethodDetailedResults::getBorders(left, right));
        if (parabolaAccepted) {
            result.iterations.back()["parabolaA"] = a;
            result.iterations.back()["parabolaB"] = b;
            result.iterations.back()["parabolaC"] = c;
        }
        result.iterations.back()["min"] = u;
    }
    result.result = x;

    return result;
}
