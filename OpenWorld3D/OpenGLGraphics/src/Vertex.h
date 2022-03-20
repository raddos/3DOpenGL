#pragma once
#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
	glm::vec3 normal;

};
