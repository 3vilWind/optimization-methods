#include "LUWrapperMatrix.h"
#include <exception>


double LWrapperMatrix::get(size_t y, size_t x) const {
    if (x == y)
        return 1;
    if (x > y)
        return 0;
    return matrix.get(y, x);
}

void LWrapperMatrix::set(size_t y, size_t x, double value) {
    throw std::exception("set is not supported!");
}

size_t LWrapperMatrix::size() const {
    return matrix.size();
}

double UWrapperMatrix::get(size_t y, size_t x) const {
    if (x < y)
        return 0;
    return matrix.get(y, x);
}

void UWrapperMatrix::set(size_t y, size_t x, double value) {
    throw std::exception("set is not supported!");
}

size_t UWrapperMatrix::size() const {
    return matrix.size();
}
