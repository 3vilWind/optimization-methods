#pragma once

#include "../Generator.h"

namespace sparse_row_column {
    class SimpleGenerator : public Generator {
    public:
        void generate(const std::string &path);
    };
}
