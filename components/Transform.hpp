
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../misc/Types.hpp"
#include "../internal/ITweakable.hpp"
#include <stdlib.h>
#include <malloc.h>
//#include "../framework/Entity.hpp"
enum class Dirty {
	None,
	Model,
	Acum,
};


class Entity;

class Transform : public ITweakable
{
private:
	Vec3_t rotation = { 0, 0, 0 };
	Vec3_t position = { 0,0,0 };
	Vec3_t scale = { 1,1,1 };
	Dirty dirty = Dirty::None;
	glm::mat4 model;
	glm::mat4 acum;

public:
	Entity * ent;
	Transform * parent;
	std::vector<Transform*> children;


	Transform(Entity *ent);

	static const Vec3_t Front;
	static const Vec3_t Right;
	static const Vec3_t Up;


	glm::mat4& GetModel();

	glm::mat4& GetAccumulated();

	Transform* SetParent(Transform *other);

	void SetDirty(Dirty newVal);

	void Translate(float, float, float);
	void Rotate(float, float, float);
	void Scale(float, float, float);

	void Translate(Vec3_t val);

	void Rotate(Vec3_t val);

	void Scale(Vec3_t val);



	bool GetClean();
	Vec3_t GetRotation() { return rotation; }
	Vec3_t GetScale() { return scale; }
	Vec3_t GetPosition() { return position; }

	Vec3_t SetRotation(Vec3_t val) { rotation = val; return val; }
	Vec3_t SetScale(Vec3_t val) { scale = val; return val; }
	Vec3_t SetPosition(Vec3_t val) { position = val; return val; }
	Vec3_t SetRotation(float x, float y, float z) { return SetRotation(Vec3_t(x, y, z)); }
	Vec3_t SetScale(float x, float y, float z) { return SetScale(Vec3_t(x, y, z)); }
	Vec3_t SetPosition(float x, float y, float z) { return SetPosition(Vec3_t(x, y, z)); }

	static glm::mat4 GetModel(Vec3_t scale, Vec3_t position, Vec3_t rotation) {
		glm::mat4 model = glm::mat4(1);
		model = glm::rotate(model, rotation.x, { 1,0,0 });
		model = glm::rotate(model, rotation.y, { 0,1,0 });
		model = glm::rotate(model, rotation.z, { 0,0,1 });
		model = glm::translate(model, position);
		return model;
	}

	unsigned int twId = -1;
	void DebugUI(TwBar *tw, unsigned int id) {
		



		char *buff = (char*)alloca(sizeof(char) * 10);
		_itoa_s((int)id, buff, 10, 10);
		twId = id;
		std::string idStr(buff);

		std::string name = "Transform "+ idStr;
		TwAddSeparator(tw, NULL, (" group='"+name+"' ").data());
		TwAddVarRW(tw, ("Rotation " + idStr).data(), TW_TYPE_DIR3F, &rotation, ("group='" + name+"'").data());

		TwAddVarRW(tw, ("Position x " + idStr).data(), TW_TYPE_FLOAT, &position.x, ("group='" + name+"'").data());
		TwAddVarRW(tw, ("Position y " + idStr).data(), TW_TYPE_FLOAT, &position.y, ("group='" + name+"'").data());
		TwAddVarRW(tw, ("Position z " + idStr).data(), TW_TYPE_FLOAT, &position.z, ("group='" + name+"'").data());

		TwAddVarRW(tw, ("Scale x " + idStr).data(), TW_TYPE_FLOAT, &scale.x, ("group='" + name+"'").data());
		TwAddVarRW(tw, ("Scale y " + idStr).data(), TW_TYPE_FLOAT, &scale.y, ("group='" + name+"'").data());
		TwAddVarRW(tw, ("Scale z " + idStr).data(), TW_TYPE_FLOAT, &scale.z, ("group='" + name+"'").data());


		//TwAddVarRW(tw, name.data(), TW_TYPE_BOOL16, NULL, NULL);
		// Add elem to bar
	}

};

