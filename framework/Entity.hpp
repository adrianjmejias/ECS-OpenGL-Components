#pragma once
#include <vector>
#include <exception>
#include <string>

#include "../components/Transform.hpp"
#include "UpdatableComponent.hpp"
class UpdatableComponent;
class StartableComponent;
class API;
class Transform;

class Entity
{
private:
	std::vector< Component* > components;
	std::vector< UpdatableComponent* > updatableComponents;

	unsigned int idTw = 0;
	bool isOn = true;


	Transform *transform;
	friend class Scene;

public:
	Entity(const std::string name);
	std::string name;

	void SetActive(bool status) {
		isOn = status;
	}


	Transform* GetTransform() {
		return transform;
	}
	unsigned int GetIdTw() {
		return idTw;
	}


	virtual ~Entity();
	virtual void Update(const API &api);

	template <typename T>
	T* GetComponent() {
		T* ret = nullptr;

		for (auto comp : components) {
			ret = dynamic_cast<T>(comp);
			if (ret) {
				return ret;
			}
		}

		return ret;
	}
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args) {
		T* ret = new T(std::forward<Args>(args)...);

		AddComponent(ret);

		return ret;
	}

	template <typename T>
	T* AddComponent(T *component) {
		if (!component) {
			throw std::exception("Component to add is null");
		}

		Component *comp  = dynamic_cast<Component*>(component);

		if (!comp) {
			throw std::exception("You are not adding a component");
		}

		if (comp->entity != nullptr) {
			Entity *stealedEntity = comp->entity;
			auto &components = stealedEntity->components;
			auto idx = std::find_if(components.begin(), components.end(), [=](Component *e) { return e == comp; });
			if (idx != components.end()) {
				components.erase(idx, idx+1);

			}


		}
		comp->entity = this;
		comp->transform = this->transform;

		UpdatableComponent *up = dynamic_cast<UpdatableComponent*>(component);

		if (up) {
			updatableComponents.push_back(up);
		}


		components.push_back(component);

		return component;
	}
private:
};
