#pragma once

//#include <glad/glad.h>
#include <glm\gtc\matrix_transform.hpp>
#include "../framework/UpdatableComponent.hpp"

enum Camera_Movement {
	FORWARD = GLFW_KEY_W,
	BACKWARD = GLFW_KEY_S,
	LEFT = GLFW_KEY_A,
	RIGHT = GLFW_KEY_D
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.f;
const float SENSITIVITY = 1.f;
const float ZOOM = 45.0f;



class Camera : public virtual UpdatableComponent, public virtual StartableComponent
{
private:
	bool dirty = true;


public:


	unsigned int power = 1;
	bool isOrtho = false;
	float fov = 45.0f;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 100.0f;
	Vec3_t front;
	Vec3_t up;
	glm::mat4 view;
	glm::mat4 projection;

	Camera() : UpdatableComponent() {

	}
	Vec2_t windowProps;

	bool isActive = false;

	virtual void Start(const API &api) {


		api.RegisterGetKeyDown(KeyCode::SPACE, [&]() {
			isActive = !isActive;
			api.SetGameMode(isActive);
		});
		api.RegisterGetKeyUp(KeyCode::SPACE, [&]() {
			isActive = !isActive;

			api.SetGameMode(isActive);
		});



		api.RegisterMouseDelta([&](double xoffset, double yoffset) {
		
			//ProcessMouseMovement(xoffset, yoffset, true);
		
		});

		api.RegisterMouseScroll([&](float,float yoffset) {
			//ProcessMouseScroll(yoffset);
		});
	}

	virtual void Update(const API &api) {
		unsigned int newWidth = api.GetWindowWidth();
		unsigned int newHeigth = api.GetWindowHeight();

		if (windowProps.x - newWidth != 0 || windowProps.y - newHeigth != 0) {
			dirty = true;
			windowProps = { newWidth, newHeigth };
			glm::vec3 pos = GetTransform().GetPosition();

			std::cout << "Camera " << std::endl;
			std::cout << "(" << pos[0] << " " << pos[1] << " " << pos[2] << ")" << std::endl;
		}
	}

public:
	bool IsDirty() {
		Transform &t = *transform;
		bool initialDirty =  dirty || t.GetClean();
		dirty = initialDirty;

		if (dirty) {
			view = Transform::GetModel(t.GetScale(), -t.GetPosition(), t.GetRotation()); //glm::lookAt(transform->GetPosition(), transform->GetPosition() + front, up);

			if (isOrtho)
			{
				projection = glm::ortho(0.f, windowProps.x, 0.f, windowProps.y, -1.f, 1.f);
			}
			else {
				projection = glm::perspective(glm::radians(fov), windowProps.x / windowProps.y, nearClippingPlane, farClippingPlane);
			}
			dirty = false;
		}
		return initialDirty;
	}









public:



	glm::mat4 GetProjectionMatrix(int w,int h) {
		projection = glm::perspective(glm::radians(fov), w / (float)h, nearClippingPlane, farClippingPlane);
		return projection;
	}


	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Component()
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{

		if (!isActive) return;
			float velocity = MovementSpeed * deltaTime;
			if (direction == FORWARD)
				Position += Front * velocity;
			if (direction == BACKWARD)
				Position -= Front * velocity;
			if (direction == LEFT)
				Position -= Right * velocity;
			if (direction == RIGHT)
				Position += Right * velocity;

		
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		if (!isActive) return;

		xoffset *= MouseSensitivity;
		yoffset *= -MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (!isActive) return;

		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
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
