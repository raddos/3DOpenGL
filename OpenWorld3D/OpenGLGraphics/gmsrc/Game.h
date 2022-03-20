#pragma once

class Game 
{
private:

	void Init();

public:
	Game();
	virtual ~Game();

	//Accessirs

	//Modifiers

	//Functions
	void Update();
	void Render();
	void Shutdown();
	
};