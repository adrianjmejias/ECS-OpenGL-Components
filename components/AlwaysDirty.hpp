#pragma once
#pragma once

#include "../framework/UpdatableComponent.hpp"
#include "../internal/API.hpp"

#include <iostream>
class API;
class AlwaysDirty : public UpdatableComponent
{
public:
	AlwaysDirty() : UpdatableComponent() {

	}



	virtual void Update(const API &api) {
		transform->SetDirty(Dirty::Model);
	}
private:

};
