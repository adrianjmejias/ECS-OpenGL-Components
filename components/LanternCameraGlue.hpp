#pragma once
#pragma once

#include "../framework/UpdatableComponent.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "../internal/API.hpp"

#include <iostream>
class API;
class LanterCameraGlue : public UpdatableComponent
{
public:
	Light &l;
	Camera &c;
	LanterCameraGlue(Light &_l, Camera &_c) :l(_l), c(_c), UpdatableComponent() {

	}


	virtual void Update(const API &api) {
		
		l.direction = c.front;
		
		//transform->Rotate(speed * (float)api.DeltaTime());
	}
private:

};
