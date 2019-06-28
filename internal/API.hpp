#pragma once
#include "../systems/SystemInput.hpp"
#include "Time.hpp"
#include "Window.hpp"


enum class KeyCode;
//class Time;

class API {
	SystemInput* c_input;
	//UI* c_ui;
	Time* c_time;
	Window* c_window;

	friend class Scene;
	bool Init() {
		

	}
public:
	
	void SetGameMode(bool mode) const {
		c_window->SetGameMode(mode);
	}

	void RegisterGetKeyDown(KeyCode k, std::function<void()> f) const {
		c_input->RegisterGetKeyDown(k,f);
	}
	void RegisterGetKeyUp(KeyCode k, std::function<void()> f) const {
		c_input->RegisterGetKeyUp(k, f);
	}
	void RegisterGetKey(KeyCode k, std::function<void()> f) const {
		c_input->RegisterGetKey(k, f);
	}
	void RegisterMouseDelta(std::function<void(double, double)> f) const {
		c_input->RegisterMouseDelta(f);
	}
	void RegisterMousePos(std::function<void(double, double)> f) const {
		c_input->RegisterMousePos(f);
	}
	void RegisterMouseScroll(std::function<void(double, double)> f) const {
		c_input->RegisterMouseScroll(f);
	}
	void RegisterMouseButtonDown(MouseButton m, std::function<void(Mod)> f) const {
		c_input->RegisterMouseButtonDown(m, f);
	}
	void RegisterMouseButtonUp(MouseButton m, std::function<void(Mod)> f) const {
		c_input->RegisterMouseButtonUp(m, f);
	}

	double DeltaTime() const {
		return c_time->DeltaTime();
	}
	unsigned int GetWindowHeight() const {
		return c_window->GetHeight();
	}
	unsigned int GetWindowWidth() const {
		return c_window->GetWidth();
	}
	void Close() const {
		c_window->Close();
	}
};
