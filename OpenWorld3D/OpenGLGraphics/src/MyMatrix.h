#pragma once

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

glm::mat4 ViewMatrix() {
	//Camera
	glm::mat4 ViewMatrix(1.f);
	glm::vec3 camPosition(0.f, 0.0f, 2.f);
	glm::vec3 lookUpWorld(0.f, 1.0f, 0.0f);
	glm::vec3 camFront(0.0f, 0.0, -1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, lookUpWorld);
	return ViewMatrix;
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
