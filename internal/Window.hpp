#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <iostream>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
//#include <imgui/imgui_impl_glfw.h>
//#include <imgui/imgui_impl_opengl3.h>

class Window {
	bool gameMode = false;
	unsigned int width = 800;
	// Window current height
	unsigned int height = 600;
	// Window title
	const char *windowTitle = "Adrian Mejias";
	// Window pointer
	GLFWwindow* window;
	friend class Scene;
	void SetSize(int width, int height) {
		this->width = width;
		this->height = height;
		TwWindowSize(width, height);
		glViewport(0,0, width, height);
	}

public:

	void SetGameMode(bool mode) {
		if (mode) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		}
	}
	unsigned int GetWidth() {
		return width;
	}
	unsigned int GetHeight() {
		return width;
	}

	GLFWwindow* Init() {

		glfwInit();

		window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		//glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE); // permite el evento press o hold
		// The window couldn't be created
		if (!window)
		{
			std::cout << "Failed to create the glfw window" << std::endl;
			glfwTerminate(); // Stops the glfw program
			return nullptr;
		}
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//
		//ImGui_ImplOpenGL3_Init();
		//ImGui_ImplGlfw_InitForOpenGL(window, true);

		//Imgui_
		return window;
	}
	~Window() {
		glfwTerminate();
	}


public: 
	void Close() {
		glfwSetWindowShouldClose(window, true);
	}
	
	bool EarlyUpdate() {
	bool close = !glfwWindowShouldClose(window);
	if (!close) {
		return true;
	}



	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return false;
}
public: void LateUpdate() {


	glfwSwapBuffers(window);
}


};