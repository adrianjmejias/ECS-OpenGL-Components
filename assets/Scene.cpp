#include "Scene.hpp"



void processInput(GLFWwindow *window){
	extern Camera *camera;
	extern Scene *scenee;
	float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(static_cast<Camera_Movement>(GLFW_KEY_W), scenee->c_api->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(static_cast<Camera_Movement>(GLFW_KEY_S), scenee->c_api->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(static_cast<Camera_Movement>(GLFW_KEY_A), scenee->c_api->DeltaTime());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(static_cast<Camera_Movement>(GLFW_KEY_D), scenee->c_api->DeltaTime());

}



static void CallbackKeyGLFW(GLFWwindow *window, int key, int scancode, int action, int mods) {
	//extern Scene scene;
	extern Scene *scenee;
	//TwEventKeyGLFW(key, action);
	scenee->KeyListener(static_cast<KeyCode>(key), action);





}

static void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods) {

	//extern Scene scene;
	extern Scene *scenee;
	scenee->MouseButton(button, action, mods);
	TwEventMouseButtonGLFW(button, action);
}

static void CallbackMousePosition(GLFWwindow *window, double xPos, double yPos) {
	//extern Scene scene;
	extern Scene *scenee;
	extern Camera *camera;

	camera->ProcessMouseMovement(scenee->c_input->mouseDeltaX , scenee->c_input->mouseDeltaY);

	scenee->MousePosition(xPos, yPos);
	TwEventMousePosGLFW(xPos, yPos); 
}
static void CallbackMouseScroll(GLFWwindow* window, double xoffset, double yoffsets) {
	//extern Scene scene;
	extern Scene *scenee;

	//TwEventMouseWheelGLFW(xoffset);
	scenee->MouseScroll(xoffset, yoffsets);
}

static void CallbackMouseIn(GLFWwindow* window, int entered) {
	//extern Scene scene;
	extern Scene *scenee;

	if (entered)
	{
		scenee->OnMouseEnter();
		// The cursor entered the content area of the window
	}
	else
	{
		scenee->OnMouseLeave();
		// The cursor left the content area of the window
	}
}

static void CallbackWindowResize(GLFWwindow*, int width, int height) {
	//extern Scene scene;
	extern Scene *scenee;
	scenee->OnWindowResize(width, height);
}

void Scene::SetCallbacks() {
	glfwSetWindowSizeCallback(c_input->window, CallbackWindowResize);
	glfwSetKeyCallback(c_input->window, CallbackKeyGLFW);
	glfwSetMouseButtonCallback(c_input->window, CallbackMouseButton);
	glfwSetCursorPosCallback(c_input->window, CallbackMousePosition);
	glfwSetScrollCallback(c_input->window, CallbackMouseScroll);
	//glfwSetCharCallback(c_window->window, (GLFWcharfun)TwEventCharGLFW);

}


void Scene::SetInput(SystemInput *input) {
	c_input = input;
}

bool Scene::Init() {


	c_window = new Window();
	c_ui = new UI();
	c_time = new Time();
	c_input = new SystemInput();
	c_api = new API();
	c_renderer = new SystemRenderer();

	GLFWwindow* window = c_window->Init();

	bool isInit = c_ui->Init();
	isInit = isInit && c_time->Init();
	isInit = isInit && window;
	isInit = isInit && c_input->Init(window);


	c_api->c_input = c_input;
	c_renderer->c_api = c_api;
	c_api->c_time = c_time;
	c_api->c_window = c_window;

	//c_window->SetSize(c_window->width, c_window->height);
	//c_camera_comp = new Camera(&c_camera);
	//c_camera.AddComponent(c_camera_comp);

	return isInit;
}

void Scene::Run() {
	c_renderer->Init();


	for (; !c_window->EarlyUpdate(); c_window->LateUpdate()) {
		//c_input->Update();

		c_time->Update([&]() {
			if (!c_input) {
				__debugbreak();
			}
			processInput(c_input->window);
			c_input->Update();

			std::queue<Entity*> callOrder; //bfs
			for (unsigned int ii = 0; ii < size(); ii++) {
				callOrder.push(at(ii).get());
			}

			while (!callOrder.empty()) {
				Entity *ent = callOrder.front();
				callOrder.pop();

				ent->Update(*c_api);
				ent->GetTransform()->GetClean();

				for (Transform *child : ent->transform->children) {
					if(child->ent)
					callOrder.push(child->ent);
				}
			}
			c_renderer->Update();
			c_ui->Update();
		});


		//UpdateMats();




	}

}

void Scene::AddEntity(std::vector<Entity*> entities) {

	for (auto ent : entities) {
		std::unique_ptr<Entity> p(ent);
		this->push_back(std::move(p));

		ITweakable * tw = dynamic_cast<ITweakable*>(ent->transform);
		if (tw) {
			c_ui->AddITweakable(tw);
		}

		for (int ii = ent->components.size() - 1; ii >= 0; ii--)
		{
			Component *comp = ent->components[ii];


			ITweakable * tw = dynamic_cast<ITweakable*>(comp);
			if (tw) {
				c_ui->AddITweakable(tw);
			}


			StartableComponent* start(dynamic_cast<StartableComponent*>(comp));

			if (start) {
				start->Start(*c_api);
			}

			ent->transform->SetDirty(Dirty::Model);

			MeshRenderer* mr = dynamic_cast<MeshRenderer*>(comp);

			if (mr) {
				c_renderer->AddRenderer(mr);
				std::swap(ent->components[ii], ent->components[ent->components.size() - 1]);
				ent->components.pop_back();
				continue;
			}

			Light* light = dynamic_cast<Light*>(comp);

			if (light) {
				c_renderer->AddLight(light);
				std::swap(ent->components[ii], ent->components[ent->components.size() - 1]);
				ent->components.pop_back();
				continue;
			}

			Camera* cam = dynamic_cast<Camera*>(comp);

			if (cam) {
				c_renderer->AddCamera(cam);
				std::swap(ent->components[ii], ent->components[ent->components.size() - 1]);
				ent->components.pop_back();
				continue;
			}
		}

	}

}

Scene::~Scene() {


	delete c_api;
	delete c_input;
	delete c_ui;
	delete c_time;
	delete c_window;
}

void Scene::KeyListener(KeyCode k, int event) {
	c_input->KeyListener(k, event);
}

void Scene::MousePosition(double xPos, double yPos) {
	//c_input->KeyListener(k, event);
	c_input->OnMousePosition(xPos, yPos);
}

void Scene::MouseButton(int button, int action, int mods) {
	//c_input->KeyListener(k, event);
	c_input->OnMouseButton(button, action, mods);
}

void Scene::MouseScroll(double xOffset, double yOffsets) {
	//c_input->KeyListener(k, event);
	c_input->OnMouseScroll(xOffset, yOffsets);
}

