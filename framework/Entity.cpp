#include "Entity.hpp"

Entity::Entity(const std::string name) {
	this->name = name;
	this->transform = new Transform(this);
}


Entity::~Entity() {
	delete transform;
}

void Entity::Update(const API &api) {
	if (isOn) {
		for (size_t ii = 0; ii < updatableComponents.size(); ii++)
		{
			updatableComponents[ii]->InternalUpdate(api);
		}
	}
}

