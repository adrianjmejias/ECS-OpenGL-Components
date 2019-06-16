#pragma once

#include <vector>
#include <array>
#include "Asset.hpp"
typedef std::array<double, 2> Vec2_t;
typedef std::array<double, 3> Vec3_t;
typedef std::array<unsigned int, 3> index_t;

class Mesh : public Asset
{
public:
    Mesh() = default;
    Mesh(Mesh &&) = default;
    Mesh(const Mesh &) = default;
    Mesh &operator=(Mesh &&) = default;
    Mesh &operator=(const Mesh &) = default;
    ~Mesh() = default;

    public: std::vector< Vec3_t > vertex;
    public: std::vector< Vec3_t > normal;
    public: std::vector< Vec2_t > uv;

    public: std::vector< index_t > face;
    public: std::vector< index_t > faceTex;
    public: std::vector< index_t > faceNorm;
private:
    
};

