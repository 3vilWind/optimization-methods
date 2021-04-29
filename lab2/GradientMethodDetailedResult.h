#pragma once

#include <vector>
#include <map>
#include <string>
#include "Vector.h"


struct GradientMethodDetailedResult {
    Vector result;
    std::vector<Vector> iterations;
};
