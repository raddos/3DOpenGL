#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

Shader::Shader(const std::string& filepath):rendererID(0),filepath(filepath)
{
	
	ShaderProgramSource source = ParseShader(filepath);
	rendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader() 
{
	GLCall(glDeleteProgram(rendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(rendererID));
}
void Shader::Unbind() const 
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string& name,const glm::mat4 matrix) 
{	//location 
	//how many matrixes
	//glm stores as collom major no need to transope matrix 
	//pointer for that point array of matrix
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform3fv(const std::string& name, float  *val)
{
	GLCall(glUniform3fv(GetUniformLocation(name),1, val));
}


int Shader::GetUniformLocation(const std::string& name) 
{

	if (uniformLocationCash.find(name) != uniformLocationCash.end())
		return uniformLocationCash[name];

	int location = glGetUniformLocation(rendererID, name.c_str());
	if (location == -1)
		std::cout << "ERROR:LOCATION NOT FOUND" << name << std::endl;
	uniformLocationCash[name] = location;
	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
{

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//TODO: Error handling

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // allocating on stack dynamically
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex info " : "Fragment info ") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
	//same as glGenbuffer
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	

	int result;
	glGetProgramiv(program,GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // allocating on stack dynamically
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Failed to link program!" << std::endl;
		std::cout << message << std::endl;
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) 
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				//set vertex mode
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
				//set fragment mode
				type = ShaderType::FRAGMENT;
		}
		else
			ss[(int)type] << line << '\n';

	}

	return { ss[0].str(),ss[1].str() };
}

