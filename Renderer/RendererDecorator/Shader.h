#pragma once
#ifndef SHADER_HEADER
#define SHADER_HEADER
#include <string>
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <map>
#include <fstream>
#include "easylogging++.h"

class Shader
{
public:
	Shader();
	const unsigned int getId(const char* shaderName);
	void setBool(const char* shaderName, const std::string& name, bool value) const;
	void setInt(const char* shaderName, const std::string& name, int value) const;
	void setFloat(const char* shaderName, const std::string& name, float value) const;
	void setVec2(const char* shaderName, const std::string& name, const glm::vec2& value) const;
	void setVec2(const char* shaderName, const std::string& name, float x, float y) const;
	void setVec3(const char* shaderName, const std::string& name, const glm::vec3& value) const;
	void setVec3(const char* shaderName, const std::string& name, float x, float y, float z) const;
	void setVec4(const char* shaderName, const std::string& name, const glm::vec4& value) const;
	void setVec4(const char* shaderName, const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const char* shaderName, const std::string& name, const glm::mat2& mat) const;
	void setMat3(const char* shaderName, const std::string& name, const glm::mat3& mat) const;
	void setMat4(const char* shaderName, const std::string& name, const glm::mat4& mat) const;
	void Init();
	void Bind(const char* shaderName);
	void UnBind(const char* shaderName);
	void setShaderNames(std::initializer_list<std::pair<char*, bool>>* Names);
	void AddShader(const char* shaderName, const char* vertexPath,
		const char* fragmentPath,
		const char* tcPath = nullptr,
		const char* tePath = nullptr,
		const char* geometryPath = nullptr);
private:
	void PushShader(std::string Name, bool tessShaders = true);
	void checkCompileErrors(GLuint shader, std::string type);
private:
	std::map<std::string, int> mShader;
	std::initializer_list<std::pair<char*, bool>> *mShaderNames = nullptr;
};

#endif // !SHADER_HEADER
