#pragma once 

#include "../misc/KeyCodes.hpp"
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>
#include <functional>

//ext

class SystemInput;



class SystemInput
{
public:
	GLFWwindow *window;
	SystemInput() = default;
	SystemInput(SystemInput &&) = default;
	SystemInput(const SystemInput &) = default;
	SystemInput &operator=(SystemInput &&) = default;
	SystemInput &operator=(const SystemInput &) = default;
	virtual ~SystemInput() = default;
	std::unordered_map<KeyCode, std::vector<std::function<void()> > > keyDown;
	std::unordered_map<KeyCode, std::vector<std::function<void()> > > keyUp;
	std::unordered_map<KeyCode, std::vector<std::function<void()> > > KeyPressed;
	std::vector < std::function<void(double, double)> > mousePos;
	std::vector < std::function<void(double, double)> > mouseDelta;
	std::vector < std::function<void(double, double)>  > mouseScroll;
	std::unordered_map <MouseButton, std::vector< std::function<void(Mod)> > > mouseButtonDown;
	std::unordered_map <MouseButton, std::vector<std::function<void(Mod)> > > mouseButtonUp;
public:bool Init(GLFWwindow* window) {
	this->window = window;
	return true;
}
public: virtual void Update() {
	
	glfwPollEvents();
}


public: void KeyListener(KeyCode k, int event) {


	switch (event)
	{
	case GLFW_PRESS:
		for (auto &callback : keyDown[k]) {
			callback();
		}
		break;
	case GLFW_RELEASE:
		for (auto &callback : keyUp[k]) {
			callback();
		}
		break;

	case GLFW_REPEAT:
		for (auto &callback : KeyPressed[k]) {
			callback();
		}
		break;
	default:
		break;
	}
}

		double yAct = 0;
		double xAct = 0;
		double yLast = 0;
		double xLast = 0;
		
public: 
	void RegisterGetKey(KeyCode k, std::function<void()> f) {
	this->KeyPressed[k].push_back(f);
}
void RegisterGetKeyDown(KeyCode k, std::function<void()> f) {
	this->keyDown[k].push_back(f);
}
void RegisterGetKeyUp(KeyCode k, std::function<void()> f) {
	this->keyUp[k].push_back(f);
}


		void RegisterMouseDelta(std::function<void(double, double)> f) {
			mouseDelta.push_back(f);
		}
		void RegisterMousePos(std::function<void(double, double)> f) {
			mousePos.push_back(f);
		}
		void RegisterMouseScroll(std::function<void(double, double)> f) {
			mouseScroll.push_back(f);
		}
		void RegisterMouseButtonDown(MouseButton m, std::function<void(Mod)> f) {
			mouseButtonDown[m].push_back(f);
		}
		void RegisterMouseButtonUp(MouseButton m, std::function<void(Mod)> f) {
			mouseButtonUp[m].push_back(f);
		}
		int mouseDeltaX, mouseDeltaY;
		void OnMousePosition(double xPos, double yPos) {
			xAct = xPos;
			yAct = yPos;
			for (auto f : mousePos) {
				f(xAct, yAct);
			}


			double deltaX = xAct - xLast;
			double deltaY = yAct - yLast;
			mouseDeltaX = deltaX;
			mouseDeltaY = deltaY;

			//std::cout << "DeltaX " << deltaX << " = " << xAct << "- "<<xLast<< std::endl;
			//std::cout << "DeltaY " << deltaY << " = " << yAct << "- "<<yLast<< std::endl;

			for (auto f : mouseDelta) {
				f(deltaX, deltaY);
			}



			yLast = yAct;
			xLast = xAct;
		}
		void OnMouseButton(int button, int action, int mods) {
			MouseButton a = static_cast<MouseButton>(button);
			Mod b = static_cast<Mod>(mods);

			if (action == GLFW_PRESS) {
				for (auto &f : mouseButtonDown[a]) {
					f(b);
				}
			}
			else if (action == GLFW_RELEASE) {
				for (auto &f : mouseButtonUp[a]) {
					f(b);
				}
			}

		}
		void OnMouseScroll(double xoffset, double yoffsets) {
			for (auto f : mouseScroll) {
				f(xoffset, yoffsets);
			}
		}
		void OnMouseEnter() {
			yLast = yAct;
			xLast = xAct;
		}
		void OnMouseLeave() {

		}

private:

};


