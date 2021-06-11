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

double Vector::norm() const {
    return sqrt((*this) * (*this));
}


Vector Vector::opposite() const {
    return (*this) * -1.f;
}

std::string Vector::to_string() const {
    std::string ans;
    for (double x : vector) {
        ans += std::to_string(x) + " ";
    }
    return ans;
}

Vector Vector::getRandomVector(size_t size, double k) {
    std::vector<double> ans;
    for (size_t i = 0; i < size; ++i) {
        ans.push_back(random(0, 2 * k) - k);
    }
    return Vector(ans);
}

std::vector<double> Vector::getPlainVector() const {
    return std::vector<double>(vector);
}

Vector operator+(Vector lhs, const Vector &rhs) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        lhs.vector[i] += rhs.vector[i];
    }
    return lhs;
}

Vector operator-(Vector lhs, const Vector &rhs) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        lhs.vector[i] -= rhs.vector[i];
    }
    return lhs;
}

Vector operator*(Vector lhs, double rhs) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        lhs.vector[i] *= rhs;
    }
    return lhs;
}

double operator*(const Vector & lhs, const Vector &rhs) {
    double ans = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        ans += lhs.vector[i] * rhs.vector[i];
    }
    return ans;
}

Vector &Vector::operator+=(const Vector &rhs) {
    for (size_t i = 0; i < size(); ++i) {
        vector[i] += rhs.vector[i];
    }
    return (*this);
}

Vector operator*(double lhs, Vector rhs) {
    return std::move(rhs) * lhs;
}

Vector operator-(const Vector &a) {
    return a.opposite();
}


std::vector<std::vector<double>> Vector::multiply(const Vector& v) const {
    std::vector<std::vector<double>> result(size(), std::vector<double>(size(), v.size()));
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            result[i][j] = this->vector[i] * v[j];
        }
    }
    return result;
}