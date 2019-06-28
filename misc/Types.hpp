#pragma once
#include <glm/glm.hpp>

typedef glm::vec2 Vec2_t;
typedef glm::vec3 Vec3_t;
typedef glm::quat Quat_t;
typedef glm::uvec3 index_t;


enum class MapType {
	AMBIENT,
	DIFFUSE,
	SPECULAR,
	SHINY,
	DISPLACEMENT,
	DECAL,
	BUMP,
	REFLECTION
};

enum class IllumModel {
	CONSTANT_COLOR,
	//	0  This is a constant color illumination model.The color is the
	//	specified Kd for the material.The formula is :
	//
	//		color = Kd


	DIFFUSE,
	//	1  This is a diffuse illumination model using Lambertian shading.The
	//	color includes an ambient constant term and a diffuse shading term for
	//	each light source.The formula is

	//		color = KaIa + Kd{ SUM j = 1..ls, (N * Lj)Ij }

	COLOR_DIFFUSE_AND_SPECULAR,

	//	2  This is a diffuse and specular illumination model using Lambertian
	//	shading and Blinn's interpretation of Phong's specular illumination
	//	model(BLIN77).The color includes an ambient constant term, and a
	//	diffuse and specular shading term for each light source.The formula
	//	is :

	//	color = KaIa
	//		+ Kd{ SUM j = 1..ls, (N*Lj)Ij }
	//		+Ks{ SUM j = 1..ls, ((H*Hj) ^ Ns)Ij }

};


enum class LightType {
	POINT,
	DIRECTIONAL,
	SPOTLIGHT
};


