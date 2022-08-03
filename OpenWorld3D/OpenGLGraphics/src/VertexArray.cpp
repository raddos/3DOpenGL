#include "VertexArray.h"
#include "Vertex.h"

#include "Renderer.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&rendererID));
}


void VertexArray::AddBuffer(const VertexBuffer& vb)
{
	this->Bind();
	vb.Bind();

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position)));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture )));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
	GLCall(glEnableVertexAttribArray(3));

	vb.Unbind();
	this->Unbind();
	
}

void VertexArray::Bind()const
{
	GLCall(glBindVertexArray(rendererID));
}

void VertexArray::Unbind()const
{
	GLCall(glBindVertexArray(0));
}