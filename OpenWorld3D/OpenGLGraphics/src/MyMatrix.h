#ifndef MYMATRIX_HEADER
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#define MYMATRIX_HEADER
glm::mat4 ModelMatrix() {
	// Attributes
	glm::vec3 position(0.f);
	glm::vec3 refposition(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);
	//setting matrix ( INNIT )
	// Indentity matrix needed for manipulation
	glm::mat4 modelMatrix(1.f); 
	
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, -4.f));
	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(35.f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(10.f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
	return modelMatrix;
}



glm::mat4 PerspectiveProj() {
	//Projection for 3d
	glm::mat4 perspectiveProj(1.0f);
	float FOV = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	perspectiveProj = glm::perspective(glm::radians(FOV), static_cast<float>(1280) / 720, nearPlane, farPlane);
	return perspectiveProj;
}


#endif MYMATRIX_HEADER
