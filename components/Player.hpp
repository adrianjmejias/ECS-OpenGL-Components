#pragma once
#include <iostream>
#include "../framework/UpdatableComponent.hpp"

class UpdatableComponent;
//class Transform;
class Player : public virtual StartableComponent{
private:
public:

	Player():StartableComponent() {

	}
	KeyCode up = KeyCode::W;
	KeyCode down = KeyCode::S;
	KeyCode left = KeyCode::A;
	KeyCode right = KeyCode::D;



	virtual void Start(const API &api) {
		//Tranform * transform = (this->entity->transform);


		api.RegisterGetKeyDown(up, [&]() {
			 transform->Translate(Vec3_t(0,1,0));
			std::cout << " Player W" << std::endl;

		});
		api.RegisterGetKeyDown(left, [&]() {
			std::cout << " Player A" << std::endl;
			 transform->Translate(Vec3_t(-1, 0, 0));


		});
		api.RegisterGetKeyDown(down, [&]() {
			std::cout << " Player S" << std::endl;
			 transform->Translate(Vec3_t(0, -1, 0));

		});

		api.RegisterGetKeyDown(right, [&]() {

			std::cout << " Player D" << std::endl;
			 transform->Translate(Vec3_t(1, 0, 0));

		});
		api.RegisterMouseDelta([](float x, float y) {
			//std::cout << x << " " << y << std::endl;
		});

		api.RegisterMouseButtonDown(MouseButton::BUTTON_RIGHT, [](Mod m) {
			//std::cout << "Click right" << std::endl;
		});



	}


	virtual void Update(const API &api) {
	}
};