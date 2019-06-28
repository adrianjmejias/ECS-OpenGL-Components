

#pragma once
#include "StartableComponent.hpp"
class API;
class UpdatableComponent;
class Entity;

class StartableComponent: public virtual Component{
	friend class Entity;
	//friend class Scene;
	//StartableComponent() = default;
protected:
	StartableComponent() : Component() {
	}
public:
	virtual ~StartableComponent() = default;
    virtual void Start(const API &api) = 0;
};
    
