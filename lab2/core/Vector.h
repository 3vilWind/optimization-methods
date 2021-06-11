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

    double norm() const;

    Vector opposite() const;

    std::vector<double> &data() {
        return vector;
    }

    std::string to_string() const;

    static Vector getRandomVector(size_t size, double k);

    std::vector<double> getPlainVector() const;

    friend Vector operator+(Vector lhs, const Vector &rhs);

    friend Vector operator-(Vector lhs, const Vector &rhs);

    friend Vector operator*(Vector lhs, double rhs);

    friend double operator*(const Vector &lhs, const Vector &rhs);

    friend Vector operator-(const Vector &a);

    Vector &operator+=(const Vector &rhs);

    friend Vector operator*(double lhs, Vector rhs);

    double &operator[](std::size_t idx) { return vector[idx]; }

    const double &operator[](std::size_t idx) const { return vector[idx]; }

    std::vector<std::vector<double>> multiply(const Vector& v) const;
};
