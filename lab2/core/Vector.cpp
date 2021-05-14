#include "Vector.h"
#include <cmath>
#include <string>
#include <utility>
#include "Utils.h"

Vector::Vector() = default;

Vector::Vector(size_t size) {
    this->vector.resize(size);
}

Vector::Vector(std::vector<double> vector) : vector(std::move(vector)) {}

size_t Vector::size() const {
    return vector.size();
}

double Vector::get(size_t index) const {
    return vector.at(index);
}

Vector Vector::add(const Vector &v1, const Vector &v2) {
    std::vector<double> ans;
    for (size_t i = 0; i < v1.size(); ++i) {
        ans.push_back(v1.get(i) + v2.get(i));
    }
    return Vector(ans);
}

Vector Vector::add(const Vector &v) const {
    return add(v, *this);
}

double Vector::scalar_multiplication(const Vector &v1, const Vector &v2) {
    double ans = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        ans += v1.get(i) * v2.get(i);
    }
    return ans;
}

double Vector::scalar_multiplication(const Vector &v) const {
    return scalar_multiplication(v, *this);
}

double Vector::norm() const {
    return sqrt(scalar_multiplication(*this, *this));
}

Vector Vector::number_multiplication(const Vector &v, double x) {
    std::vector<double> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        ans.push_back(v.get(i) * x);
    }
    return Vector(ans);
}

Vector Vector::number_multiplication(double x) const {
    return Vector::number_multiplication(*this, x);
}

Vector Vector::opposite() const {
    return Vector::number_multiplication(-1);
}

std::string Vector::to_string() const {
    std::string ans;
    for (double x : vector) {
        ans += std::to_string(x) + " ";
    }
    return ans;
}

Vector Vector::random_vector(size_t size, double k) {
    std::vector<double> ans;
    for (size_t i = 0; i < size; ++i) {
        ans.push_back(random(0, 2 * k) - k);
    }
    return Vector(ans);
}


