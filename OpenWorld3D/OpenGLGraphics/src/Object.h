#pragma once
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Primitive.h"
#include "Texture.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

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
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, 0.f));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f));
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


class Object {

public:
	Object() {};
	virtual ~Object() {};
	virtual void Render() {};
	virtual void Update() {};
	virtual void InitAttributes() {}
};

class CubeObject : public Object
{
protected:
	//for filelocation
	const char* shaderFilepath;
	//Shape
	Primitive* cube;
	//Basic attributes
	Shader* shader; 
	Renderer* renderer;
	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;

	//Default attributes
	glm::mat4 modelMatrix = ModelMatrix();
	glm::mat4 viewMatrix = ViewMatrix();
	glm::mat4 perpectiveProj = PerspectiveProj();

public:

	bool setPlay;

	CubeObject(const char* shaderFilepath) :Object(), shaderFilepath(shaderFilepath)
	{
		this->setPlay = false;
		InitAttributes();
		InitDefaultParameters();
		UnbindAll();

	}
	~CubeObject()
	{
		delete shader;
		delete renderer;
		delete va;
		delete vb;
		delete ib;
		delete cube;
		delete shaderFilepath;
	}

	virtual void InitAttributes() {
		shader = new Shader(shaderFilepath);
		shader->Bind();
		this->cube = new Cube();
		this->va = new VertexArray(); // vertex array object
		vb = new VertexBuffer(cube->getNumberOfVertices(), cube->getVertices());  // buffer vertices data 
		va->AddBuffer(*this->vb); // adding to pointers to data
		ib = new IndexBuffer(cube->getNumberOfIndices(), cube->getIndices()); // given idices 
		shader->Unbind();

	}
	void Render(Renderer * renderer) {

		renderer->Draw(*this->va, *this->ib, *this->shader);

	}
	void Update() {
		
	};

	void RotateXAxis(float degree) {
		shader-> Bind();
		this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(1.f, 0, 0));
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	}

	void setPlayer() {
		this->setPlay = true;
		TranslateMatrixLeftAndRight(0.f);
		TranslateMatrixNearAndFar(-2.f);
		TranslateMatrixUpAndDown(0.f);
		std::cout << to_string(this->modelMatrix);
	}
	
	//between -1 and +1
	void TranslateMatrixUpAndDown(float y) {
		shader->Bind();
		this->modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, y, 0.0f));

		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	};
	//between -1 and +1
	void TranslateMatrixLeftAndRight(float x) {
		shader->Bind();
		this->modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0.f, 0.f));

		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	};
	void TranslateMatrixNearAndFar(float z) {
		shader->Bind();
		this->modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, z));

		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	};

	void SetTexture(std::string TextureUniformName,const int &value){
		shader->Bind();
		shader->SetUniform1i(TextureUniformName,value);
		shader->Unbind();
	}

private:

	void InitDefaultParameters() {

		shader->Bind();
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->SetUniformMat4f("u_ViewMatrix", viewMatrix);
		shader->SetUniformMat4f("u_PerspectiveProjection", perpectiveProj);

		glm::vec3 lightPos(0.f, 0.f, 2.f);
		glm::vec3 camPosition(0.f, 0.0f, 1.f);

		shader->SetUniform3fv("lightPos", glm::value_ptr(lightPos));
		shader->SetUniform3fv("camPosition", glm::value_ptr(camPosition));
		shader->Unbind();
	}


public:
	void UnbindAll() {
		va->Unbind();
		vb->Unbind();
		ib->Unbind();
		shader->Unbind();
	}

	void BindAll() {
		va->Bind();
		vb->Bind();
		ib->Bind();
		shader->Bind();
	}

};
