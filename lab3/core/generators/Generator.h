#pragma once
#include <string>


class Generator {
public:
    virtual void generate(const std::string& path) = 0;
};
