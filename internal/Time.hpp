#pragma once

#include <GLFW/glfw3.h>
#include <functional>



 typedef double time__;
class Time{
	time__ time, dt;

    public:
    bool Init(){
		dt = 0;
		time = glfwGetTime();
		return true;
    }

    void Update(std::function<void()> f){
        dt = glfwGetTime() - time;
		if (dt <= 0) dt = 0;
		else{
			f();
		}
		time += dt;
    }

	time__ DeltaTime(){
        return dt;
    }
};