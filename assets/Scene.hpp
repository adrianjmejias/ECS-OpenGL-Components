#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
#include "../internal/ITweakable.hpp"
#include "../loaders/Shader.hpp"
#include "../internal/API.hpp"
#include "../framework/UpdatableComponent.hpp"
#include "../internal/SystemRenderer.hpp"
#include "../framework/Entity.hpp"
//#include "../components/Transform.hpp"
#include "../internal/UI.hpp"
//#include "../internal/Time.hpp"
//#include "../internal/Window.hpp"



//class SystemRenderer;
class Scene : private std::vector<std::unique_ptr<Entity> >
{
	friend class API;
	friend class Scene;
public:
	Scene() = default;
	Scene(Scene &&) = default;
	Scene(const Scene &) = default;
	Scene &operator=(Scene &&) = default;
	Scene &operator=(const Scene &) = default;
	~Scene();

	void SetInput(SystemInput *input);
	bool Init();
	void AddEntity(std::vector<Entity*>);
	void Run();
	void SetCallbacks();
	void KeyListener(KeyCode k, int event);
	void MousePosition(double, double);
	void MouseButton(int, int,int);
	void MouseScroll(double, double);
	void OnMouseEnter() {
		c_input->OnMouseEnter();
	}
	void OnMouseLeave() {
		c_input->OnMouseLeave();

	}

	void OnWindowResize(int width, int height) {
		//TwWindowSize(width, height);
		c_window->SetSize(width, height);
	}




	API* c_api;
	SystemInput* c_input;
	SystemRenderer* c_renderer;
	UI* c_ui;
	Time* c_time;
	Window* c_window;
private:

	glm::mat4 projection;
	glm::mat4 view;
	friend class Entity;
};
