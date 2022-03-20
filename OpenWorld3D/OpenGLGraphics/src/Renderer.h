#pragma once

#include <glad/glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

class IndexBuffer;

class VertexArray;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError(); 
bool GLLogCall(const char* function, const char* file, int line); 




class Renderer {

private:

public:
	void Clear()const;
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
};