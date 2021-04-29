#pragma once

#include <vector>

class Vector {
private:
    std::vector<double> vector;

public:
    explicit Vector(std::vector<double> vector);

    Vector();

    explicit Vector(size_t size);

    size_t size();

    double get(size_t index);

    static Vector add(Vector v1, Vector v2);

    Vector add(Vector v);

    static double scalar_multiplication(Vector v1, Vector v2);

    double scalar_multiplication(Vector v);

    double norm();

    static Vector number_multiplication(Vector v, double x);

    Vector number_multiplication(double x);

    Vector opposite();

    std::string to_string();

    static Vector random_vector(size_t size, double k);
};
