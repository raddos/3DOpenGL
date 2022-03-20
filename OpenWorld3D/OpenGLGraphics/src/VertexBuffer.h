#pragma once
#include "Vertex.h"
struct Vertex;

class VertexBuffer 
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(const int numberOfVertices, Vertex* verticesData);
	~VertexBuffer();

	void Bind() const ;
	void Unbind() const ;

	void SetData() {};
	void GetData() {};
	void LockData() {};
	void UnlockData() {};
};