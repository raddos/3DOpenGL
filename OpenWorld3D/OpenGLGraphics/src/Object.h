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
	static int initcounter() {
		static int k = 0;
		k += 1;
		return k;
	};

	bool setPlay;

	CubeObject(Shader * shader,int textureSlot) :Object(), shader(shader){
		initcounter();
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
		delete cube;
		delete shader;
		delete shaderFilepath;
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
private:

	void InitDefaultParameters(int textureSlot) {

		shader->Bind();
		std::cout << to_string(modelMatrix);
		shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader->SetUniformMat4f("u_ViewMatrix", viewMatrix);
		shader->SetUniformMat4f("u_PerspectiveProjection", perpectiveProj);

		glm::vec3 lightPos(0.f, 0.f, 2.f);
		glm::vec3 camPosition(0.f, 0.0f, 1.f);

		shader->SetUniform3fv("lightPos", glm::value_ptr(lightPos));
		shader->SetUniform3fv("camPosition", glm::value_ptr(camPosition));

		//adds to shader
		shader->SetUniform1i("uniformTexture", textureSlot);
		shader->Unbind();
	}


};

class TerrainMesh {
private:
	Shader* shader;
	int xSize;
	int zSize;
protected:

	CubeObject* cube;
	int textureSlot;
	std::vector<CubeObject*> cubes;

public:

	TerrainMesh(Shader * shader,
		int xSize, int zSize,int textureSlot) :shader(shader), zSize(zSize), xSize(xSize),textureSlot(textureSlot)
	{
		Init();

	};

	~TerrainMesh() {
		for (auto* cube : cubes) {
			delete cube;
		}
		this->cubes.empty();
	}

	void Init() {

		// x by z size
		//4 x 4 / 2 x 2 
		// -2 - 2 x y / -1 0 1  
		int xNeg =-( xSize / 2);
		int xPos = xSize / 2;

		int zNeg = -(zSize / 2);
		int zPos = zSize / 2;

		for (int i = xNeg ; i < xPos; i ++)
		{
			for (int j = zNeg; j<zPos;j++)
			{
				this->cube = new CubeObject(shader,textureSlot);
				this->cube->TranslateMatrixLeftAndRight((float)i);
				this->cube->TranslateMatrixNearAndFar((float)j);
				this->cube->TranslateMatrixUpAndDown((float)-1.f);
				cubes.push_back(cube);
				
			}
		}
		std::cout << "Cubes size for terrain : " << cubes.size();
	}

	void Draw(Renderer * renderer) {
		for (auto& cube : cubes)
		{
			
			cube->Draw(renderer);
		}
	}
	void Update() {
		for (auto &cube : cubes)
		{
			cube->RotateXAxis(10);
		}
	}
};

