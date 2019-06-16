#pragma once
#include "Asset.hpp"

class Material : public Asset
{
public:
    Material() = default;
    Material(Material &&) = default;
    Material(const Material &) = default;
    Material &operator=(Material &&) = default;
    Material &operator=(const Material &) = default;
    ~Material() = default;

private:
    
};