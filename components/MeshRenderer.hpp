#pragma once

//#include "../loaders/ShaderProgram.hpp"
#include "../assets/Mesh.hpp"
#include "../framework/StartableComponent.hpp"
#include <memory>
#include <functional>
//#include "../loaders/Shader.hpp"
#include "../internal/ITweakable.hpp"




class MeshRenderer : virtual public Component, public ITweakable
{
private:
	friend class SystemRenderer;

public:
	Mesh *mesh;
	MeshRenderer(Mesh* mesh) : Component() {
		this->mesh = mesh;
	}

public:
	bool useTextures = true;



	void DebugUI(TwBar *tw, unsigned int id) {

		char *buff = (char*)alloca(sizeof(char) * 10);
		_itoa_s((int)transform->twId, buff, 10, 10);

		std::string idStr(buff);
		std::string name = "Material " + idStr;

		Material &mat = *mesh->materials[0];


		std::string nameGroup = "Transform " + idStr;
		TwAddSeparator(tw, ("Material "+mat.name + idStr).data(), ("group='" + nameGroup + "'").data());

		TwAddVarRW(tw, ("Mat Color " + idStr).data(), TW_TYPE_COLOR3F, &mat.color, ("group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Mat Specular " + idStr).data(), TW_TYPE_COLOR3F, &mat.specular, ("group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Mat Diffuse " + idStr).data(), TW_TYPE_COLOR3F, &mat.diffuse, ("group='" + nameGroup + "'").data());


		TwAddVarRW(tw, ("Mat Shiny " + idStr).data(), TW_TYPE_FLOAT, &mat.shiny, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Mat Rough " + idStr).data(), TW_TYPE_FLOAT, &mat.rough, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Mat Reflectance " + idStr).data(), TW_TYPE_FLOAT, &mat.reflectance, ("step=0.1 group='" + nameGroup + "'").data());

		//TwAddVarRW(tw, name.data(), TW_TYPE_BOOL16, NULL, NULL);
		// Add elem to bar
	}

};
