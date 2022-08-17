#include "Test.h"
#include "Primitive.h"
#include "Sound.h"
#include "Gui.h"
#include "Window.h"
#include "Texture.h"
#include "Terrain.h"
#include "PrimitiveObjects.h"

void playerInput(GLFWwindow* win, CubeObject* cube,float deltaTime);

Test::Test() 
{

}

Test::~Test()
{

}

void Test::Play() const
{
	//Windows
	Window win;

	//sound
	Sound s;
	s.testSound();
	Renderer renderer;

	//Terrain init
	Shader terrainShader("res/shaders/terrain.shader");
	Texture terrainTexture("res/textures/TextureDirt.jpg");
 	Terrain terrain(&terrainShader, 32,32, 0);
	
	//Player init 
	Shader *playerShader= new Shader("res/shaders/player.shader");
	Texture playerTexture("res/textures/SwordImage.png");
	CubeObject* player= new CubeObject(playerShader, 1);

	player->speed = 25.f;
	//Coin init
	Shader* coinShader = new Shader("res/shaders/player.shader");
	Texture coinTexture("res/textures/coin.png");
	CubeObject* coin = new CubeObject(coinShader, 2);

	//Enemy 

	//Binding textures
	terrainTexture.BindTextureSlot();
	playerTexture.BindTextureSlot();
	coinTexture.BindTextureSlot();

	//Gui
	Gui GUI;
	GUI.Init(win.getWindowsPointer());

	coin->TranslateMatrixLeftAndRight(2.f,1.0f);

	bool flagAliveForCoin = true;

	while (!win.windowShouldClose())
	{
		
		win.curTime = glfwGetTime();
		win.deltaTime = win.curTime - win.lastTime;

	 
		//Update
		glfwPollEvents();
		GUI.Update();
		//Input
		win.processInputForWindow();
		
		//Player Input
		playerInput(win.getWindowsPointer(), player, win.deltaTime);


		//Rendering commands here
		renderer.Clear();
		//Terrain & SkyBox
		terrain.Draw(&renderer);

		//Player& Coins
		player->Draw(&renderer);

		//Check objects with shaders 
		if(flagAliveForCoin)
			coin->Draw(&renderer);
		
		GUI.UpdateTime(&win.curTime);
		//Enemies & Score
		if (player->CheckPos(*coin)) {
			//check pos
			GUI.UpdateScore();
			flagAliveForCoin = false;
		}
		if (flagAliveForCoin) {
		//	std::cout << "Player position :  " << glm::to_string(player->positions) << std::endl;
		//	std::cout << "Coin Posisiton : " << glm::to_string(coin->positions) << std::endl;
		}
		//Gui
		GUI.Render();
		


		win.lastTime = win.curTime;
		win.swapBuffers();
	}

	GUI.Shutdown();
	win.Shutdown();
	return ;
}


void playerInput(GLFWwindow* win,CubeObject * cube,float deltaTime) 
{
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		cube->TranslateMatrixNearAndFar(-0.1f,deltaTime);
	if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		cube->TranslateMatrixNearAndFar(+0.1f, deltaTime);
	if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(-0.1f, deltaTime);
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(+0.1f, deltaTime);
	//Sprint
	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cube->speed = 100.f;
}

