#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

class Shader
{
private:
	unsigned int rendererID;
	std::string filepath;
	std::unordered_map<std::string, int> uniformLocationCash;
public:
	Shader(const std::string& filepath);
	~Shader();
	inline std::string getShaderFilePath()  const {
		return filepath;
	}
	void Bind() const;
	void Unbind() const;
	//Set uniforms 
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);
	void SetUniform3fv(const std::string& name, float* val);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
