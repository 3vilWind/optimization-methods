#pragma once

#include "../Generator.h"

namespace symmetric_profile {
    class HilbertGenerator : public Generator {
    public:
        void generate(const std::string &path) override;
    };
}