#pragma once
#include "../misc/Types.hpp"

#include "Asset.hpp"
#include "../loaders/ShaderProgram.hpp"
#include "Texture.hpp"
#include <memory>
#include <unordered_map>




class Material : public Asset
{
public:


	std::shared_ptr<ShaderProgram> shader;


	Material(std::string name = "default material") {
		this->name = name;
	};
	


    Material(Material &&) = default;
    Material(const Material &) = default;
    Material &operator=(Material &&) = default;
    Material &operator=(const Material &) = default;

	Vec3_t color{ 0,0,0 };
    Vec3_t diffuse{1,1,1};
	Vec3_t specular{ 1,1,1 };
	Vec3_t emissive{ 1,1,1 };
	float dissolve = 1.f;
	float shiny = 128.f;
	float rough = 0.3f;
	float refractionIndex = 0.3f;
	float covariance = 0.3f;
	float reflectance = 0.3f;

	std::unordered_map<MapType, std::shared_ptr<Texture> >  maps;
	

    //std::unordered_map<std::string, float> otherParams;
private:
    
};