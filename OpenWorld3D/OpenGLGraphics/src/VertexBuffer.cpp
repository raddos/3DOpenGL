#include "VertexBuffer.h"
#include "Renderer.h"



VertexBuffer::VertexBuffer(const int numberOfVertices,  Vertex* verticesData)
{
	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER,numberOfVertices * sizeof(Vertex) , verticesData, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1,&rendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
