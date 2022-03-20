#pragma once
#include "Vertex.h"

class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int count;
public:
	IndexBuffer(const unsigned int numberOfIndices, const unsigned int * indicesData);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const ;

	inline unsigned int GetCount() const { return count; };

	void SetData() {};
	void GetData() {};
	void LockData() {};
	void UnlockData() {};
};