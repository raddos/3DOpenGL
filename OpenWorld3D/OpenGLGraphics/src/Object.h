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
#include "MyMatrix.h"


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

	int textureSlot;
public:
	bool setPlay;
	CubeObject(Shader * shader,int textureSlot) :Object(), shader(shader),textureSlot(textureSlot) {
		
		this->setPlay = false;
		InitAttributes();
		InitDefaultParameters(textureSlot);
		UnbindAll();
	}
	

	~CubeObject()
	{
		delete va;
		delete vb;
    	delete ib;
    	delete shader;
		delete cube;
	}

	virtual void InitAttributes() {
		this->cube = new Cube();
		this->va = new VertexArray(); // vertex array object
		vb = new VertexBuffer(cube->getNumberOfVertices(), cube->getVertices());  // buffer vertices data 
		va->AddBuffer(*this->vb); // adding to pointers to data
		ib = new IndexBuffer(cube->getNumberOfIndices(), cube->getIndices()); // given idices 
	}
	void Draw(Renderer * renderer) {

		renderer->Draw(*this->va, *this->ib, *this->shader);

	};

	void Delete() {
		shader->Bind();
		this->modelMatrix = glm::mat4(0.f);
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	}

	void RotateXAxis(float degree) {
		shader-> Bind();
		this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(1.f, 0, 0));
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	}

	void RotateYAxis(float degree) {
		shader->Bind();
		this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(0, 1.0f, 0));
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	}
	void RotateZAxis(float degree) {
		shader->Bind();
		this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(0, 0, 1.f));
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->Unbind();
	}

	void setPlayer() {
		this->setPlay = true;
		TranslateMatrixLeftAndRight(0.f);
		TranslateMatrixNearAndFar(-2.f);
		TranslateMatrixUpAndDown(0.f);
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

	void Update() {

		//shader->SetUniform3fv("camPosition", glm::value_ptr(camPosition));
	}

private:

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
	void InitDefaultParameters(int textureSlot) {

		shader->Bind();
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->SetUniformMat4f("u_ViewMatrix", viewMatrix);
		shader->SetUniformMat4f("u_PerspectiveProjection", perpectiveProj);

		glm::vec3 lightPos(0.f, 0.f, 2.f);
		glm::vec3 camPosition(0.f, 0.0f, 1.f);

		shader->SetUniform3fv("lightPos", glm::value_ptr(lightPos));

		//adds to shader
		shader->SetUniform1i("uniformTexture", textureSlot);
		shader->Unbind();
	}


};
// Texture slot 2 shader//
// making terrain 
// Texture 
class Terrain
{
private:
	int xSize;
	int zSize;
protected:
	int textureSlot;
public:
	std::vector<CubeObject*> tiles;
	Shader * shader;
	Terrain(Shader * shader,
		int xSize, int zSize,int textureSlot) :shader(shader), zSize(zSize), xSize(xSize),textureSlot(textureSlot)
	{

		Init();
		std::cout << tiles.size();
	};

	~Terrain() {
		tiles.clear();
		
	}
	void Init() 
	{
		for (int i = -(xSize/2); i < (xSize/2); i++)
		{
			for (int j = -(zSize/2); j < zSize/2; j++) {
				this->shader = new Shader(shader->getShaderFilePath());
				CubeObject* cube = new CubeObject(shader, textureSlot);
				cube->TranslateMatrixLeftAndRight((float)i);
				cube->TranslateMatrixNearAndFar((float)j);
				cube->TranslateMatrixUpAndDown((float)-1.f);
				tiles.push_back(cube);
			}
		}
	}

	void Draw(Renderer * renderer) {
		for (auto& tile : tiles)
		{
			tile->Draw(renderer);
		}
	}
	void Update() {
	}
};

