#pragma once
#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
	glm::vec3 normal;

	friend std::ostream& operator<<(std::ostream& os, const Vertex vert)
	{
		os << " Position : " + glm::to_string(vert.position) << " Color : " + glm::to_string(vert.color) << "Texture : " + glm::to_string(vert.texture) << " Normals : " + glm::to_string(vert.normal) << std::endl;
		return os;
	}

	void getSize() {
		std::cout << "Size of vertex: " + sizeof(Vertex);
	}


};
