#pragma once


inline void shift2(double &a, double &b, const double c) {
    a = b;
    b = c;
}

inline void shift3(double &a, double &b, double &c, const double d) {
    a = b;
    b = c;
    c = d;
}

inline double SIGN(const double &a, const double &b) {
    return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

void getParabolaCoefficients(double x1, double y1, double x2, double y2, double x3, double y3,
                             double &a, double &b, double &c);

double getParabolaMinimum(double x1, double y1, double x2, double y2, double x3, double y3);