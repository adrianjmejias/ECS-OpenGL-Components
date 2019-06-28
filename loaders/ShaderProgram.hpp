#pragma once

#include "Shader.hpp"
#include <memory>
#include <vector>

class ShaderProgram : private std::vector< std::shared_ptr<Shader> >
{
private:
	unsigned int id;
public:
	ShaderProgram() = default;
	ShaderProgram(ShaderProgram &&) = default;
	ShaderProgram(const ShaderProgram &) = default;
	ShaderProgram &operator=(ShaderProgram &&) = default;
	ShaderProgram &operator=(const ShaderProgram &) = default;
	~ShaderProgram() {
		std::cout << "Die ShaderProgram" << std::endl;
	};
	unsigned int Get();
	void ReCompile();
	void AddShader(std::shared_ptr<Shader> shader);
	void Compile();

	/**
	* Enables the shader to be use
	*/
	void  use();

	/**
	* Sets a bool uniform
	* @param{std::string &} uniform name
	* @param{bool} value to be set
	*/
	void  setBool(const std::string &name, bool value) const;

	/**
	* Sets an int uniform
	* @param{std::string &} uniform name
	* @param{int} value to be set
	*/
	void  setInt(const std::string &name, int value) const;

	/**
	* Sets an int uniform
	* @param{std::string &} uniform name
	* @param{float} value to be set
	*/
	void  setFloat(const std::string &name, float value) const;

	/**
	* Sets an vec2 uniform
	* @param{std::string &} uniform name
	* @param{vec2} value to be set
	*/
	void  setVec2(const std::string &name, const glm::vec2 &value) const;

	/**
	* Sets an vec2 uniform
	* @param{std::string &} uniform name
	* @param{float} vec2 x value
	* @param{float} vec2 y value
	*/
	void  setVec2(const std::string &name, float x, float y) const;

	/**
	* Sets an vec3 uniform
	* @param{std::string &} uniform name
	* @param{vec3} vector value
	*/
	void  setVec3(const std::string &name, const glm::vec3 &value) const;

	/**
	* Sets an vec3 uniform
	* @param{std::string &} uniform name
	* @param{float} vec3 x value
	* @param{float} vec3 y value
	* @param{float} vec3 z value
	*/
	void  setVec3(const std::string &name, float x, float y, float z) const;

	/**
	* Sets an vec4 uniform
	* @param{std::string &} uniform name
	* @param{vec4} vec4 value
	*/
	void  setVec4(const std::string &name, const glm::vec4 &value) const;

	/**
	* Sets an vec4 uniform
	* @param{std::string &} uniform name
	* @param{float} vec4 x value
	* @param{float} vec4 y value
	* @param{float} vec4 z value
	* @param{float} vec4 w value
	*/
	void  setVec4(const std::string &name, float x, float y, float z, float w);

	/**
	* Sets an mat2 uniform
	* @param{std::string &} uniform name
	* @param{mat2} mat2 value
	*/
	void  setMat2(const std::string &name, const glm::mat2 &mat) const;

	/**
	* Sets an mat3 uniform
	* @param{std::string &} uniform name
	* @param{mat3} mat3 value
	*/
	void  setMat3(const std::string &name, const glm::mat3 &mat) const;

	/**
	* Sets an mat4 uniform
	* @param{std::string &} uniform name
	* @param{mat4} mat4 value
	*/
	void  setMat4(const std::string &name, const glm::mat4 &mat) const;
};
