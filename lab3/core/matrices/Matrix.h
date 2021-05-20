#pragma once


class Matrix {
public:
    virtual double get(size_t y, size_t x) const = 0;

    virtual void set(size_t y, size_t x, double value) = 0;

    virtual size_t size() const = 0;
};
