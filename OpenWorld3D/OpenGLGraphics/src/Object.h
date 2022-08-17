#pragma once
//Renderer
#include "Renderer.h"


class Object {

public:
	Object() = default;
	~Object() = default;
	virtual void Draw(Renderer* renderer) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void InitAttributes() = 0;
};

