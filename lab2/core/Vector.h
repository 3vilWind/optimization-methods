#pragma once

#include <vector>
#include <string>

class Vector {
private:
    std::vector<double> vector;

public:
    explicit Vector(std::vector<double> vector);

    Vector();

    explicit Vector(size_t size);

    size_t size() const;

    double get(size_t index) const;

    static Vector add(const Vector &v1, const Vector &v2);

    Vector add(const Vector &v) const;

    static double scalar_multiplication(const Vector &v1, const Vector &v2);

    double scalar_multiplication(const Vector &v) const;

    double norm() const;

    static Vector number_multiplication(const Vector &v, double x);

    Vector number_multiplication(double x) const;

    Vector opposite() const;

    std::string to_string() const;

    static Vector random_vector(size_t size, double k);
};
