#pragma once
#include "VertexBuffer.h"

class VertexBuffer;

class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb);
	void Bind() const;
	void Unbind() const;


};