#include "Renderer.h"
#include <iostream>
#include <sstream>

void GLClearError() 
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{

	while (GLenum error = glGetError())
	{
		std::stringstream shex;
		shex << std::hex << (int)error;
		std::string hex(shex.str());

		std::cout << "[OpenGL Error] (hex :0x" << hex << ") " << function <<
			" " << file << " " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear()const {
		glClearColor(0.5f, 0.0f, 0.0f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//Render
		GLCall(glEnable(GL_DEPTH_TEST));// allowing z coord
		GLCall(glEnable(GL_CULL_FACE)); // cullign somethin that we dont want to see
		GLCall(glCullFace(GL_BACK));// back side not want to be seen
		GLCall(glFrontFace(GL_CCW));//counter clock wise vertices to be drawn
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));// Object to be filled with color ( GL_LINES= outline,GL_FILL = shape)


		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // blend alpha pix ( source pix  1-source = dest
		GLCall(glEnable(GL_BLEND)); // belnding of colors 

}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const 
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}