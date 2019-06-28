#pragma once

#include "../framework/StartableComponent.hpp"
#include "../internal/API.hpp"

#include <iostream>
class API;
class CSDeathCam : public StartableComponent, public UpdatableComponent
{
public:
	CSDeathCam() : StartableComponent() {
		Position = { 0,0,-15 };
		WorldUp = { 0,1,0 };
		Yaw = -90.0f;
		Pitch = 0.0f;
		updateCameraVectors();
	}

	KeyCode keyUp = KeyCode::W;
	KeyCode keyDown = KeyCode::S;
	KeyCode keyLeft = KeyCode::A;
	KeyCode keyRight = KeyCode::D;
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed = -1;
	float MouseSensitivity = 1;
	float Zoom=1;

	Camera* camera;
	bool isActive = false;

	virtual void Update(const API &api) {
		//camera->front = Front;
		//camera->up = Up;
		//updateCameraVectors();
		//camera->view = GetViewMatrix();

	}


	glm::mat4 viewMat;
	virtual void Start(const API &api) {

		//api.RegisterGetKeyDown(KeyCode::SPACE, [&]() {
		//	isActive = !isActive;
		//	api.SetGameMode(isActive);
		//});
		//api.RegisterGetKeyUp(KeyCode::SPACE, [&]() {
		//	isActive = !isActive;

		//	api.SetGameMode(isActive);
		//});



		//api.RegisterGetKeyDown(keyUp, [&]() {
		//	if (isActive) {
		//		transform->Translate(Front * MovementSpeed);

		//	}
		//});
		//api.RegisterGetKeyDown(keyDown, [&]() {
		//	if (isActive) {
		//		transform->Translate(-Front * MovementSpeed);
		//	}
		//});

		//api.RegisterGetKeyDown(keyLeft, [&]() {

		//	// se supone que esto es el right que lo podría cachear

		//	if (isActive) {
		//		transform->Translate(-Right * MovementSpeed);
		//	}

		//});
		//api.RegisterGetKeyDown(keyRight, [&]() {

		//	if (isActive) {
		//		transform->Translate(Right *MovementSpeed);
		//	}


		//});
		//api.RegisterMouseDelta([&](float x, float y) {
		//	if (isActive) {
		//		x *= MouseSensitivity;
		//		y *= MouseSensitivity;

		//		Yaw += x;
		//		Pitch += y;

		//		// Make sure that when pitch is out of bounds, screen doesn't get flipped

		//		if (Pitch > 89.0f)
		//			Pitch = 89.0f;
		//		if (Pitch < -89.0f)
		//			Pitch = -89.0f;

		//		//transform->SetRotation(Vec3_t(Pitch, Yaw, 0));
		//		// Update Front, Right and Up Vectors using the updated Euler angles
		//		updateCameraVectors();
		//	}



		//});

		//api.RegisterMouseScroll([&](float x, float y) {
		//	if (isActive) {
		//		if (Zoom >= 1.0f && Zoom <= 45.0f)
		//			Zoom -= y;
		//		if (Zoom <= 1.0f)
		//			Zoom = 1.0f;
		//		if (Zoom >= 45.0f)
		//			Zoom = 45.0f;
		//	}

		//});



	}
private:
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
