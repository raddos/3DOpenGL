#include "PrimitiveObjects.h"

#include "MyMatrix.h"
CubeObject::CubeObject(Shader* shader, int textureSlot) : Object(), shader(shader), textureSlot(textureSlot)
{
	this->setPlay = false;
	InitAttributes();
	InitMatrices();
	InitDefaultParameters(textureSlot);
	UnbindAll();
}

CubeObject::~CubeObject()
{
	delete va;
	delete vb;
	delete ib;
	delete shader;
	delete cube;
}


void CubeObject::Draw(Renderer* renderer) {

	renderer->Draw(*this->va, *this->ib, *this->shader);

};

void CubeObject::Delete() {
	shader->Bind();
	this->modelMatrix = glm::mat4(0.f);
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
	delete this;
}

void CubeObject::Update(float deltaTime)
{

}

#pragma region Translation

//between -1 and +1
void CubeObject::TranslateMatrixUpAndDown(float y, float deltaTime) {
	shader->Bind();
	this->modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, y * deltaTime * speed, 0.0f));
	this->positions.y += (y * speed * deltaTime);
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
};
void CubeObject::TranslateMatrixLeftAndRight(float x, float deltaTime) 
{
	shader->Bind();
	this->modelMatrix = glm::translate(modelMatrix, glm::vec3(x * deltaTime * speed, 0.f, 0.f));
	this->positions.x += (x * speed * deltaTime);
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
};
void CubeObject::TranslateMatrixNearAndFar(float z, float deltaTime)
{
	shader->Bind();
	this->modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.f, z * deltaTime * speed));
	this->positions.z += (z*speed*deltaTime);
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
};

#pragma endregion

#pragma region Rotation

//Rotation 
void CubeObject::RotateXAxis(float degree)
{
	shader->Bind();
	this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(1.f, 0, 0));
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
}

void CubeObject::RotateYAxis(float degree) {
	shader->Bind();
	this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(0, 1.0f, 0));
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
}
void CubeObject::RotateZAxis(float degree) {
	shader->Bind();
	this->modelMatrix = glm::rotate(modelMatrix, glm::radians(degree), glm::vec3(0, 0, 1.f));
	shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	shader->Unbind();
}
#pragma endregion

#pragma region Collision
bool CubeObject::CheckPos(CubeObject& cb)
{
	//position [0] / [1] / [2]
	//check x axis
	std::cout << "Postion Player: " << glm::to_string(this->positions) << "  :  Coin: " << glm::to_string(cb.positions) << std::endl;
	if (glm::abs(this->positions.x - cb.positions.x) < this->scale.x + cb.scale.x)
	{
		std::cout << "Postion X : " << positions.x << "  :  " << cb.positions.x << std::endl;
		//check the Y axis
		if (glm::abs(this->positions.y - cb.positions.y) < this->scale.y + cb.scale.y)
		{
		std::cout << "Postion Y : " << positions.y << "  :  " << cb.positions.y << std::endl;
			//check the Z axis
			if (glm::abs(cb.positions.z  - this->positions.z) < this->scale.z + cb.scale.z)
			{
				std::cout << "Postion Z : " << positions.z << "  :  " << cb.positions.z << std::endl;
				cb.Delete();
				std::cout << "Hit -> delete ";
				return true;
			}
		}
	}
	return false;
}
#pragma endregion

#pragma region PrivateDefaultParams
void CubeObject::BindAll() const {
	va->Bind();
	vb->Bind();
	ib->Bind();
	shader->Bind();
}
void CubeObject::UnbindAll() const {
	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();
}

void CubeObject::InitDefaultParameters(int textureSlot) {
	speed = 1.f;
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

void CubeObject::InitAttributes()
{
	this->cube = new Cube();
	this->va = new VertexArray(); // vertex array object
	vb = new VertexBuffer(cube->getNumberOfVertices(), cube->getVertices());  // buffer vertices data 
	va->AddBuffer(*this->vb); // adding to pointers to data
	ib = new IndexBuffer(cube->getNumberOfIndices(), cube->getIndices()); // given idices 
}

void CubeObject::InitMatrices()
{
	this->modelMatrix = ModelMatrix();
	this->perpectiveProj = PerspectiveProj();
	this->viewMatrix = ViewMatrix();
}
#pragma endregion