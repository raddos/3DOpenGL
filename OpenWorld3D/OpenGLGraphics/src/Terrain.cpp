#include "Terrain.h"
#include "Camera.h"

Terrain::Terrain(Shader* shader,
	int xSize, int zSize, int textureSlot) :shader(shader), 
	zSize(zSize), xSize(xSize), textureSlot(textureSlot)
{

	Init();
	std::cout << tiles.size();
};

Terrain::~Terrain() {
	tiles.clear();

}

//Making cubes with shaders/objects for map
void Terrain::Init()
{
	for (int i = -(xSize / 2); i < (xSize / 2); i++)
	{
		for (int j = -(zSize / 2); j < zSize / 2; j++) {
			this->shader = new Shader(shader->getShaderFilePath());
			shaders.push_back(shader);
			CubeObject* cube = new CubeObject(shader, textureSlot);
			cube->TranslateMatrixLeftAndRight((float)i, 1.f);
			cube->TranslateMatrixNearAndFar((float)j, 1.f);
			cube->TranslateMatrixUpAndDown((float)-1.f, 1.f);
			tiles.push_back(cube);
		}
	}
}

void Terrain::Draw(Renderer* renderer) {
	for (auto& tile : tiles)
	{
		tile->Draw(renderer);
	}
}
void Terrain::Update(float deltaTime)
{
	for (auto& tile : tiles) 
	{
		tile->Update(deltaTime);
	}
}