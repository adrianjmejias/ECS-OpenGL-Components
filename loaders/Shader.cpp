#include "Shader.hpp"

Shader::Shader(const std::string path, unsigned int type) {
	name = "no name";
	this->type = type;
	this->path = path;
}

void Shader::ReCompile() {
	SetFromFile(path, type);
}

void Shader::SetFromString(const std::string salsa, unsigned int type) {
	src = std::move(salsa);
	this->type = type;

	const char* c_str = src.data();
	
	if(id)
	GLCall(glDeleteShader(id));

	GLCall(id = glCreateShader(type));

	GLCall(glShaderSource(id, 1, &c_str, 0));

	GLCall(glCompileShader(id));

	int success;

	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		int length;

		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = static_cast<char*>(alloca(length * sizeof(char)));

		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile shader" << Shader::GetShaderName(type) << std::endl;
		std::cout << message;

	}
	std::cout << "shader compiled: " << name << std::endl;
}


void Shader::SetFromFile(std::string path, unsigned int type) {
	name = path;
	this->path = path;
	std::string shaderCode;
	std::ifstream shaderFile;

	// Set exceptions for ifstream object

	try
	{
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		// Open the file
		shaderFile.open(path);
		std::stringstream shaderStream;
		// Reads the buffer content into streams
		shaderStream << shaderFile.rdbuf();
		// Close the file handler
		shaderFile.close();
		// Convert the stream into a string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER Error reading file: " << path << std::endl;
		std::cout << e.what() << std::endl;
		return;
	}
	SetFromString(shaderCode, type);
}

Shader::~Shader() {
	GLCall(glDeleteShader(id));
}