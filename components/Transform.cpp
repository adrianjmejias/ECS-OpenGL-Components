
#include "Transform.hpp"
#include <GLFW/glfw3.h>
const Vec3_t Transform::Right = { 1,0,0 };
const Vec3_t Transform::Up = { 0,1,0 };
const Vec3_t Transform::Front = { 0,0,1 };



void Transform::SetDirty(Dirty newVal) {
	if (dirty == Dirty::Model) {
		return;
	}

	dirty = newVal;
}

Transform* Transform::SetParent(Transform *other) {
	if (!other) {
		throw std::exception("Not implemented yet");
		return nullptr;
	};

	if (parent == other) {
		return this; // it is done already
	}

	if (other->parent == this) {
		throw std::exception("CICLO INFINITO POR GAFO EN LA JERARQUíA\n");
	}
	//ponerme a mi de padre
	SetDirty(Dirty::Acum);

	parent = other; // el es mi padre

	other->children.push_back(this);// yo soy su hijo

	return this;
}

glm::mat4& Transform::GetAccumulated() {
	GetClean();
	return acum;
}

glm::mat4& Transform::GetModel() {
	GetClean();
	return model;
}

Transform::Transform(Entity *ent) {
	this->ent = ent;
}

void Transform::Translate(Vec3_t val) {
	this->position += val;
	SetDirty(Dirty::Model);
}

void Transform::Rotate(Vec3_t val) {

	const Vec3_t min = Vec3_t(0);
	const Vec3_t max = Vec3_t(360);
	
	this->rotation = glm::clamp(rotation+ val, min, max);
	if (this->rotation.x == max.x) { this->rotation.x = min.x; }
	if (this->rotation.y == max.y) { this->rotation.y = min.y; }
	if (this->rotation.z == max.z) { this->rotation.z = min.z; }
	SetDirty(Dirty::Model);
}

void Transform::Scale(Vec3_t val) {
	this->scale += val;
	SetDirty(Dirty::Model);
}

bool Transform::GetClean() {
	dirty = Dirty::Model;
	if (dirty == Dirty::None) return false;


	if (dirty == Dirty::Model) {
		model = glm::mat4(1);
		//T R S VERTEX
		model = glm::scale(model, this->scale);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.x), Vec3_t(1, 0, 0));
		model = glm::rotate(model, glm::radians(rotation.y), Vec3_t(0, 1, 0));
		model = glm::rotate(model, glm::radians(rotation.z), Vec3_t(0, 0, 1));

		dirty = Dirty::Acum; // IMPORTANTEEEEEE SINO LOS HIJOS NO SE ACTUALIZAN
	}


	if (dirty == Dirty::Acum) {
		if (parent == nullptr) {
			acum = model;
		}
		else
		{
			acum = parent->GetAccumulated() * model;
		}

		for (auto child : children) {
			child->SetDirty(Dirty::Acum);
		}
	}

	dirty = Dirty::None; 
	return true;
}

void Transform::Translate(float x, float y, float z) {
	Translate(Vec3_t(x, y, z));

}

void Transform::Rotate(float x, float y, float z) {
	Rotate(Vec3_t(x, y, z));
}

void Transform::Scale(float x, float y, float z) {
	Scale(Vec3_t(x, y, z));

}