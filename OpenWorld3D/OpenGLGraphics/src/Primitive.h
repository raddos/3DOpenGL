#pragma once
#include "Vertex.h"
#include <vector>

class Primitive {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
public:
	Primitive() {};
	virtual ~Primitive() {};

	void set(const Vertex* vertices,const int numberOfVertices,
			 const unsigned int* indices,const int numberOfIndices) 
	{
		for (size_t i = 0; i < numberOfVertices; i++) {
			this->vertices.push_back(vertices[i]);
		}
		for (size_t i = 0; i < numberOfIndices; i++) {
			this->indices.push_back(indices[i]);
		}
		
	}
	inline Vertex* getVertices() { return this->vertices.data(); }
	inline unsigned int * getIndices() { return this->indices.data(); }
	inline const size_t getNumberOfVertices() {return this->vertices.size(); }
	inline const size_t getNumberOfIndices() { return this->indices.size(); }
};

class Quad :public Primitive {
public:
	Quad() : Primitive(){
		//vertex data for square front
		Vertex vertices[] =
		{
			// positon						//color						//texture				//normals
			glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.f,0.0f,0.0f),	 glm::vec2(0.f,0.f),    glm::vec3(0.f,0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f,1.0f,0.0f),	 glm::vec2(1.f,0.f),	glm::vec3(0.f,0.0f, 1.0f),
			glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.f,1.f),    glm::vec3(0.0f,0.0f,1.0f),
			glm::vec3(-0.5f,  0.5f,0.0f),	glm::vec3(0.3f,0.5f,0.2f),	 glm::vec2(0.0f,1.0f),	glm::vec3(0.0f,0.0f, 1.0f),
		};
		//bottom side
		//dots indexing ccl for squere
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		this->set(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
	}
	virtual ~Quad() {

	}
};

class Triangle :public Primitive {
public:
	Triangle () : Primitive() {
		//vertex data for square front
		Vertex vertices[] =
		{
			// positon						//color						//texture				//normals
			glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.f,0.0f,0.0f),	 glm::vec2(0.f,0.f),    glm::vec3(0.f,0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f,1.0f,0.0f),	 glm::vec2(1.f,0.f),	glm::vec3(0.f,0.0f, 1.0f),
			glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec3(0.0f,0.0f,1.0f),	 glm::vec2(1.f,1.f),    glm::vec3(0.0f,0.0f,1.0f),
			glm::vec3(-0.5f,  0.5f,0.0f),	glm::vec3(0.3f,0.5f,0.2f),	 glm::vec2(0.0f,1.0f),	glm::vec3(0.0f,0.0f, 1.0f),
		};
		//bottom side
		//dots indexing ccl for squere
		unsigned int indices[] = {
			0, 1, 2,
		};

		this->set(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
	}
	virtual ~Triangle() {

	}
};

class Pyramid : public Primitive {
public:
		Pyramid()
			: Primitive()
		{
			Vertex vertices[] =
			{
				//Position								//Color							//Texcoords					//Normals
				//Triangle front
				glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
				glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

				//Triangle left
				glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
				glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
				glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

				//Triangle back
				glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
				glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
				glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

				//Triangles right
				glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
				glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
				glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			};
			unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

			this->set(vertices, nrOfVertices, nullptr, 0);
		}
		~Pyramid() {};
};

class Cube : public Primitive{
public:
	Cube()	: Primitive()
	{
		Vertex vertices[] =
		{
			//Position front 0,1,2,3				//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			//Position Back
			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),


		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			6,1,0,0,7,6,
			2,5,4,4,3,2,
			0,3,4,4,7,0,
			2,1,6,6,5,2

		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};
