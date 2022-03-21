#pragma once
#include "Vertex.h"
#include <vector>

class Primitive {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
public:
	Primitive();
	virtual ~Primitive();

	void set(const Vertex* vertices, const int numberOfVertices,
			 const unsigned int* indices, const int numberOfIndices);

	Vertex* getVertices();
	unsigned int* getIndices();
	const size_t getNumberOfVertices();
	const size_t getNumberOfIndices();
};

class Quad :public Primitive 
{
public:
	Quad();
	virtual ~Quad();
};

class Triangle :public Primitive 

{
public:
	Triangle();
	virtual ~Triangle();
};

class Pyramid : public Primitive 
{
public:
	Pyramid();
	~Pyramid();
};

class Cube : public Primitive
{
public:
	Cube();
	~Cube();
};
