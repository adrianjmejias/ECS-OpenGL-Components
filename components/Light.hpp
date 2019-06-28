#pragma once
#include "../framework/StartableComponent.hpp"
#include "../internal/ITweakable.hpp"




class Light : public Component , public ITweakable
{
public:
	static Vec3_t ambient;
	static float ambientStrength;
	LightType type = LightType::POINT;
	//Vec3_t col{1,0,0};
	Vec3_t color{0,0,0};
	Vec3_t diffuse{ 1,1,1 };
	Vec3_t specular{ 1,1,1 };
	Vec3_t attenuation{ 1,0,0 };

	Vec3_t direction{0,0,1};

	float innerAngle = 15.f;
	float outterAngle = 20.f;

	Light(LightType type) : Component(){
		this->type = type;
	}
	Vec3_t GetDirection() {
		glm::mat4 m = glm::mat4(1);
		glm::vec3 rotation = GetTransform().GetRotation();

		m = glm::rotate(m, rotation.x, { 1,0,0 });
		m = glm::rotate(m, rotation.y, { 0,1,0 });
		m = glm::rotate(m, rotation.z, { 0,0,1 });

		glm::vec4 v4 = glm::vec4(1, 0, 0, 1);

		v4 = m * v4;
		return v4;
	}

	void DebugUI(TwBar *tw, unsigned int id) {

		char *buff = (char*)alloca(sizeof(char) * 10);
		_itoa_s((int)transform->twId, buff, 10, 10);

		std::string idStr(buff);
		std::string name = "Light " + idStr;



		std::string nameGroup = "Transform " + idStr;
		TwEnumVal enumLights[] = {
			{ static_cast<int>(LightType::POINT) , "POINT" },
		{ static_cast<int>(LightType::DIRECTIONAL) , "DIRECTIONAL" },
		{ static_cast<int>(LightType::SPOTLIGHT) , "SPOTLIGHT" },
		};
		TwType twEnumLights = TwDefineEnum(("LightTypes " + idStr).data(), enumLights, 3);

		TwAddVarRW(tw, ("IsOn " + idStr).data(), TW_TYPE_BOOL8, &isOn, ("group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Light Type " + idStr).data(), twEnumLights, &type, ("group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Color " + idStr).data(), TW_TYPE_COLOR3F, &color, (" group='" + nameGroup+"'").data());
		TwAddVarRW(tw, ("Specular " + idStr).data(), TW_TYPE_COLOR3F, &specular, ("group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Diffuse " + idStr).data(), TW_TYPE_COLOR3F, &diffuse, ("group='" + nameGroup + "'").data());


		TwAddVarRW(tw, ("Attenuation x" + idStr).data(), TW_TYPE_FLOAT, &attenuation.x, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Attenuation y" + idStr).data(), TW_TYPE_FLOAT, &attenuation.y, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Attenuation z" + idStr).data(), TW_TYPE_FLOAT, &attenuation.z, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("InnerAngle " + idStr).data(), TW_TYPE_FLOAT, &innerAngle, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("OuterAngle " + idStr).data(), TW_TYPE_FLOAT, &outterAngle, ("step=0.1 group='" + nameGroup + "'").data());
		TwAddVarRW(tw, ("Direction " + idStr).data(), TW_TYPE_DIR3F, &direction, ("group='" + nameGroup + "'").data());

		//TwAddVarRW(tw, name.data(), TW_TYPE_BOOL16, NULL, NULL);
		// Add elem to bar
	}


private:
    
};


