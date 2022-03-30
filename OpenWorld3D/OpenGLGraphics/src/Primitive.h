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

	virtual void Print();
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



class Circle : public Primitive {
	private:
		double PI = 3.14159; //rad
		float piDegree = 180.f; // degree
		Vertex *circleVertices;
		std::vector<Vertex> circleDots;
		Vertex* vertices;
	public:
		Circle() 
		{

		
			for (float i = 0.f; i < 2 * (this->PI); i += static_cast<float>(this->PI)/ 10.f) {
		 	    this->circleVertices=new Vertex();
				circleVertices->position = glm::vec3(sin(i), cos(i), 1.f);
				circleVertices->color = glm::vec3(0.3f, 0.2f, 0.7f);
				circleVertices->texture = glm::vec2(1.f, 0.5f);
				circleVertices->normal = glm::vec3(0.f, 0.f, -1.f);	
				this->circleDots.push_back(*circleVertices);
			}
			vertices = circleDots.data();

			this->set(vertices, sizeof(vertices), 0, 0);
		};
		~Circle() {
		};
};