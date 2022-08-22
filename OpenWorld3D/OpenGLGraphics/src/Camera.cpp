#include "Camera.h"


Camera::Camera() 
{
	InitBasicVec();
	InitCameraVec();
	InitMatrix();

}

Camera::~Camera() = default;

//Positions, etc
#pragma region Setters and Getters

glm::vec3 Camera::GetCameraPosition() const {
	return cameraPos;
}

void Camera::SetCameraPosition( glm::vec3 cameraPos,float deltaTime)
{
	this->cameraPos += (cameraPos*deltaTime);
}

//For direction of camera 
glm::vec3 Camera::GetCameraTarget() {
	return this->cameraTarget;
}
void Camera::SetCameraTarget(glm::vec3 targetPosition, float deltaTime) {
	this->cameraTarget = targetPosition;
}

//For mouse rotation
glm::vec3 Camera::GetCameraFront()const {
	return this->cameraFront;
}
void Camera::SetCameraFront(glm::vec3 cameraFront, float deltaTime)
{
	this->cameraFront = cameraFront;
}

glm::vec3 Camera::GetCameraRight()const
{
	return cameraRight;
}
void Camera::SetCameraRight(glm::vec3 camerRight, float deltaTime)
{
	this->cameraRight = cameraRight;
}


#pragma endregion

//ViewMatrix
glm::mat4 Camera::GetViewMatrix()  const
{
	return this->viewMatrix;
}
void Camera::SetViewMatrix(glm::mat4 viewMatrix)
{
	this->viewMatrix = viewMatrix;
}


void Camera::Update(float deltaTime)
{
	this->InitMatrix();

};

void Camera::InitBasicVec() {
	this->up = glm::vec3(0.f, 1.f, 0.f);
}

//Defs
void Camera::InitCameraVec() 
{
	this->cameraPos = glm::vec3(0.f, 0.0f, 1.f);
	this->cameraTarget = glm::vec3(0.f);
	this->cameraDirection = glm::normalize(glm::vec3(cameraPos - cameraTarget));

	this->cameraRight =glm::normalize( glm::cross(up, cameraDirection));
	this->cameraUp = glm::cross(cameraDirection, cameraRight);
	this->cameraFront = glm::vec3(0.f, 0.0f, -1.0f);
}

void Camera::InitMatrix()
{
	
	this->viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, up);

}



