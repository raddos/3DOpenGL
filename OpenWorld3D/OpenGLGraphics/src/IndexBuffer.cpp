#include "IndexBuffer.h"
#include "Renderer.h"



IndexBuffer::IndexBuffer(const unsigned int numberOfIndices, const unsigned int * indicesData)
{
	count = numberOfIndices;
	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID)); 
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices*sizeof(unsigned int),indicesData, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1,&rendererID));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
