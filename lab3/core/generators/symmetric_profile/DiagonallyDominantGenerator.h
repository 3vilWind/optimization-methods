#pragma once

#include "../Generator.h"

namespace symmetric_profile {
    class DiagonallyDominantGenerator : public Generator {
    public:
        void generate(const std::string &path);
    };
}