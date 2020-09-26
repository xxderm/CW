#pragma once
#ifndef SHADER_HEADER
#define SHADER_HEADER
#include "RendererDecorator.h"

class Shader final : public RendererDecorator
{
public:
	Shader(Renderer* renderer);
	const unsigned getId();
	void Use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void Create(const char* vertexPath,
		const char* fragmentPath,
		const char* tcPath = nullptr,
		const char* tePath = nullptr,
		const char* geometryPath = nullptr);
private:
	void checkCompileErrors(GLuint shader, std::string type);
private:
	unsigned mId;
};

#endif // !SHADER_HEADER
