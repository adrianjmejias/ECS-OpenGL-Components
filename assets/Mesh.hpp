#pragma once
#include "../misc/Types.hpp"

#include <glm//glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Material.hpp"
#include "Asset.hpp"
#include <vector>
#include <array>
//#include "Texture.hpp"

class Mesh : public Asset
{
public:
	Mesh() = default;
	Mesh(Mesh &&) = default;
	Mesh(const Mesh &) = default;
	Mesh &operator=(Mesh &&) = default;
	Mesh &operator=(const Mesh &) = default;
	~Mesh() = default;

public:
	unsigned int VBO = 0;
	unsigned int VBO_NORM_VERTEX = 0;
	unsigned int VBO_UV = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;

	bool hasNormals = false;
	bool hasUVs = false;

	std::vector<std::shared_ptr<Material> > materials;

	std::vector< Vec3_t > vertex;
	std::vector< Vec3_t > vertexNormal;
	std::vector< Vec3_t > uv;

	std::vector< index_t > face;
	std::vector< index_t > faceTex;
	std::vector< index_t > faceNorm;

private:

};

