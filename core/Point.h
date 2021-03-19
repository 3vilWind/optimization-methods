#pragma once

struct Point {
    double x{};
    double y{};

    Point()= default;
    explicit Point(double x, double y): x(x), y(y) {}
};
