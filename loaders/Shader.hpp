#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../assets/Asset.hpp"


bool GLLogCall(const char* function, const char* file, int line);


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::string errName = "";
		switch (error)
		{
		case(0x0500):
			errName = "GL_INVALID_ENUM";
			break;
		case(0x0501):
			errName = "GL_INVALID_VALUE";
			break;
		case(0x0502):
			errName = "GL_INVALID_OPERATION";
			break;
		case(0x0505):
			errName = "GL_OUT_OF_MEMORY";
			break;
		default:break;
		}



		std::cout << "[OpenGL Error " << file << "|" << line << ")" << std::endl;
		std::cout << "Call " << function << std::endl;
		std::cout << "File: " << file << std::endl;
		std::cout << "Line: " << line << std::endl;
		std::cout << " Error code " << std::hex << error << ": " << errName << std::endl;
		std::cout << "]" << std::endl;
		return false;
	}

	return true;
}


class Shader : public Asset {
	std::string src;
	unsigned int id = 0;
	int type;
public:
	unsigned int Get() { return id; }

	Shader(const std::string path, unsigned int type);

	void ReCompile();

	void SetFromString(const std::string salsa, unsigned int type);

	void SetFromFile(std::string path, unsigned int type);

	~Shader();
private:
	static std::string GetShaderName(const unsigned int type) {

		switch (type)
		{
		case GL_VERTEX_SHADER:
			return "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			return "fragment";
			break;
		case GL_GEOMETRY_SHADER:
			return "geometry";
			break;
		}
		return "not defined";
	}

};
