#include "Primitive.h"


Primitive::Primitive() {};
Primitive::~Primitive() {};

void Primitive::set(const Vertex* vertices, const int numberOfVertices,
				const unsigned int* indices, const int numberOfIndices)
{
	for (size_t i = 0; i < numberOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
	for (size_t i = 0; i < numberOfIndices; i++) 
	{
		this->indices.push_back(indices[i]);
	}
}


Vertex* Primitive::getVertices() { return this->vertices.data(); }
unsigned int* Primitive::getIndices() { return this->indices.data(); }
const size_t Primitive::getNumberOfVertices() { return this->vertices.size(); }
const size_t Primitive::getNumberOfIndices() { return this->indices.size(); }

void Primitive::Print() { };

Quad::Quad() : Primitive() 
{
	//vertex data for square front
	Vertex vertices[] =
	{
		// positon						//color						//texture				//normals
		glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(0.f,0.f),    glm::vec3(0.f,0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(1.f,0.f),	glm::vec3(0.f,0.0f, 1.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(1.f,1.f),    glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(-0.5f,  0.5f,0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),	glm::vec3(0.0f,0.0f, 1.0f),
	};
	//bottom side
	//dots indexing ccl for squere
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	this->set(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
	
}

Quad::~Quad() {}


Triangle::Triangle() : Primitive() {
//vertex data for square front
	Vertex vertices[] =
	{
	// positon						//color						//texture				//normals
	glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(0.f,0.f),    glm::vec3(0.f,0.0f, 1.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(1.f,0.f),	glm::vec3(0.f,0.0f, 1.0f),
	glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(1.f,1.f),    glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(-0.5f,  0.5f,0.0f),	glm::vec3(0.f,0.0f,0.0f),	 glm::vec2(0.0f,1.0f),	glm::vec3(0.0f,0.0f, 1.0f),
	};
	//bottom side
	//dots indexing ccl for squere
	unsigned int indices[] = {
			0, 1, 2,
	};

	this->set(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
}

Triangle::~Triangle() {}

Pyramid::Pyramid(): Primitive()
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

	this->set(vertices, nrOfVertices, nullptr, 1);
}
	
Pyramid::~Pyramid() {};



Cube::Cube() : Primitive()
{
	Vertex vertices[] =
	{
		//Position front 0,1,2,3				//Color							//Texcoords					//Normals
		glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		//Position Back
		glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		//Positon left	
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
		//Positon right
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
		//Position up
		glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),
		//Position down
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.4f,0.1f,0.0f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),

	};
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		//Front
		0,1,2,2,3,0,
		//Back
		4,5,6,6,7,4,
		//Left
		8,9,10,10,11,8,
		//Right
		12,13,14,14,15,12,
		//Up
		16,17,18,18,19,16,
		//Down
		20,23,22,22,21,20

	};
	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Cube::~Cube(){}


