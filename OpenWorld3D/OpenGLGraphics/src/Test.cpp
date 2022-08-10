#include "Test.h"
#include "Primitive.h"
#include "Object.h"
#include "Sound.h"
#include "Gui.h"
#include "Window.h"

void playerInput(GLFWwindow* win, CubeObject* cube);

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
 	Terrain terrain(&terrainShader, 16, 16, 0);
	
	//Player init 
	Shader *playerShader= new Shader("res/shaders/player.shader");
	Texture playerTexture("res/textures/SwordImage.png");
	CubeObject* player= new CubeObject(playerShader, 1);

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

	coin->TranslateMatrixLeftAndRight(2.f);

	while (!win.windowShouldClose())
	{

		//Update
		glfwPollEvents();
		GUI.Update();
		//Input
		win.processInputForWindow();
		//Player Input
		playerInput(win.getWindowsPointer(), player);


		//Rendering commands here
		renderer.Clear();
		//Terrain & SkyBox
		terrain.Draw(&renderer);

		//terrain->Update();
		//Player& Coins
		player->Draw(&renderer);
		coin->Draw(&renderer);
		//Enemies & Score
		
		//Gui
		GUI.Render();
		
		win.swapBuffers();
	}

	GUI.Shutdown();
	win.Shutdown();
	return ;
}


void playerInput(GLFWwindow* win,CubeObject * cube) 
{
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
	{
		cube->TranslateMatrixNearAndFar(-0.1f);
	}
	if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		cube->TranslateMatrixNearAndFar(+0.1f);
	if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(-0.1f);
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(+0.1f);
	if (glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
		cube->Delete();
}

