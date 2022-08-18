#pragma once
#include "Object.h"
//Data
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Primitive.h"
//Shader
#include "Shader.h"


class CubeObject : public Object
{
private:
	//Shape
	Primitive* cube;
	//Basic attributes
	Shader* shader;
	Renderer* renderer;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	//Default attributes
	glm::mat4 modelMatrix;
	glm::vec3 scale = glm::vec3(0.5f);
	//Camera
	glm::mat4 viewMatrix;
	//View
	glm::mat4 perpectiveProj;

	float* data;
	int textureSlot;

public:
	glm::vec3 positions = glm::vec3(0.0f, 0.0f, 0.0f);
	//Variables for player 
	float speed;
	bool setPlay;
	CubeObject(Shader* shader, int textureSlot);
	~CubeObject();
	//Render
	void Draw(Renderer* renderer);
	//Logicly easier to use in gameloops
	void Delete();
	//Player input
	void Update(float deltaTime);
	//Rotation
	void RotateXAxis(float degree);
	void RotateYAxis(float degree);
	void RotateZAxis(float degree);

	//Translation
	void TranslateMatrixUpAndDown(float y, float deltaTime);
	void TranslateMatrixLeftAndRight(float x, float deltaTime);
	void TranslateMatrixNearAndFar(float z, float deltaTime);

	// Collision
	bool CheckPos(CubeObject& cb);
private:
	//Matrices;
	void InitMatrices();
	//Shader attributes
	void InitDefaultParameters(int textureSlot);
	//vao/vbo/ebo
	void InitAttributes();
	//Bindings
	void UnbindAll() const;
	void BindAll() const;
};
