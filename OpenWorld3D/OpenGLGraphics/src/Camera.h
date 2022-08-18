#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera {
private:
	//Vector declerations;
	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;

	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::mat4 viewMatrix;

	//Basic vectors
	glm::vec3 up;


	//Singleton 
	Camera();
public:
	~Camera();

	//once instance of camera for game
	static Camera &getInstance()
	{
		static Camera cam;
		return cam;
	}

	//Position for Player inputs ( walking )
	glm::vec3 GetCameraPosition() const;
	void SetCameraPosition(glm::vec3 cameraPos, float deltaTime);

	//For direction of camera 
	glm::vec3 GetCameraTarget();
	void SetCameraTarget(glm::vec3 targetPosition, float deltaTime);
	
	//For mouse rotation
	glm::vec3 GetCameraFront()const;
	void SetCameraFront(glm::vec3 cameraFront, float deltaTime);

	//ViewMatrix
	glm::mat4 GetViewMatrix() const;
	void SetViewMatrix(glm::mat4 viewMatrix);

	void Update(float deltaTime);

private:
	//initilize basic vec
	void InitBasicVec();
	//initilize vectors for camera;
	void InitCameraVec();
	//View Matrix init
	void InitMatrix();
};