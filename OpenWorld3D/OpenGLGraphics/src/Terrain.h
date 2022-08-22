#pragma once

#include "PrimitiveObjects.h"

class Terrain
{
public:
	Terrain(Shader* shader, int xSize, int zSize, int textureSlot);
	~Terrain();
	void Draw(Renderer* renderer);
	void Update(float deltaTime);
protected:
	int textureSlot;
private:
	int xSize;
	int zSize;
	std::vector<CubeObject*> tiles;
	std::vector<Shader*> shaders;
	Shader* shader;

private:
	//Terrain generator sq/sq
	void Init();
};

