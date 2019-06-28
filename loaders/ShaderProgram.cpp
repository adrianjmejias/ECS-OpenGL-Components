#include "ShaderProgram.hpp"

void ShaderProgram::Compile() {

	GLCall(id = glCreateProgram());
	std::cout << "Loading Program with --------------------------------------------------------" << std::endl;

	for (size_t ii = 0; ii < size(); ii++)
	{
		Shader &shader = *(at(ii));
		shader.ReCompile();
		GLCall(glAttachShader(id, shader.Get()));

	}

	GLCall(glLinkProgram(id));
	int success;

	//GLCall(glValidateProgram(id));

	//glGetProgramiv(id, GL_VALIDATE_STATUS, &success);

	//if(!success){
	//	// lo dejo asi pa ver si es necesario implementar esto y sacar un mensaje serio
	//	std::cout<< "Error validating"<<std::endl; 

	//	int length;

	//	GLCall(glGetProgramiv(id, GL_validate_, &length));

	//	char* message = static_cast<char*>(alloca(length * sizeof(char)));

	//	GLCall(glGetProgramInfoLog(id, length, &length, message));

	//	std::cout << "Failed to validate program :(" << std::endl;
	//	std::cout << message;


	//	__debugbreak();
	//}


	GLCall(glGetProgramiv(id, GL_LINK_STATUS, &success));

	if (!success)
	{
		int length;

		GLCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = static_cast<char*>(alloca(length * sizeof(char)));

		GLCall(glGetProgramInfoLog(id, length, &length, message));

		std::cout << "Failed to compile program :(" << std::endl;
		std::cout << message;

	}


	std::cout << "Program loaded --------------------------------------------------------" << std::endl;
}

void ShaderProgram::AddShader(std::shared_ptr<Shader> shader) {
	push_back(shader);
}

void ShaderProgram::ReCompile() {
	for (size_t ii = 0; ii < size(); ii++)
	{
		Shader &shader = *at(ii);
		shader.ReCompile();

	}
	Compile();
}

unsigned int ShaderProgram::Get() {
	return id;
}

void ShaderProgram::use()
{
	GLCall(glUseProgram(id));
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform1i(loc, (int)value));
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform1i(loc, value));
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform1f(loc, value));
}

void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform2fv(loc, 1, &value[0]));
}

void ShaderProgram::setVec2(const std::string &name, float x, float y) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform2f(loc, x, y));
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform3fv(loc, 1, &value[0]));
}

void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform3f(loc, x, y, z));
}

void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform4fv(loc, 1, &value[0]));
}

void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w)
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniform4f(loc, x, y, z, w));
}

void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]));
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	GLCall(unsigned int loc = glGetUniformLocation(id, name.c_str()));
	GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]));
}
