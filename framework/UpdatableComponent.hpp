#pragma once
#include <memory>
#include <string>

#include "Component.hpp"

#include "Entity.hpp"

class Transform;
class Entity;
class API;
class UpdatableComponent : public virtual Component
{
	friend class Entity;

private:
	void InternalUpdate(const API &api) {
		if (isOn) {
			Update(api);
		}
	}
protected:
	UpdatableComponent() : Component() {
	}

public:
	virtual ~UpdatableComponent() = default;
	virtual void Update(const API &api) = 0;
};
