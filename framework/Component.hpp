#pragma once

#include <string>

class Transform;
class Entity;
class API;
class Component
{
private:
	Entity *entity;
protected:
	Transform *transform;
	std::string name;
	Component() {
	}
public:
	bool isOn = true;
	friend class Entity;
	virtual ~Component() = default;


	virtual Entity& GetEntity() {
		return *entity;
	}
	virtual Transform& GetTransform() {
		return *transform;
	}

};
