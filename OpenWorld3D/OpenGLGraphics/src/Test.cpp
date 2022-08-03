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
	Shader *terrainShader=new Shader("res/shaders/terrain.shader");
	TerrainMesh* terrain = new TerrainMesh(terrainShader, 8, 8,0);
	Texture terrainTexture("res/textures/TextureDirt.jpg");
	//Player init 
	Shader *playerShader= new Shader("res/shaders/player.shader");
	CubeObject* player= new CubeObject(playerShader, 1);
	Texture playerTexture("res/textures/SwordImage.png");


	//Binding textures
	terrainTexture.BindTextureSlot();
	playerTexture.BindTextureSlot();
	

	//Gui
	Gui GUI;
	GUI.Init(win.getWindowsPointer());


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
		terrain->Draw(&renderer);
		

		//Player & Coins
		player->Draw(&renderer);



		//Enemies & Score
		
		
		//Gui
		GUI.Render();
		
		win.swapBuffers();
	}

	GUI.Shutdown();
	win.Shutdown();
	return ;
}


void playerInput(GLFWwindow* win,CubeObject * cube) {
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
		cube->TranslateMatrixNearAndFar(-0.1f);
	}
	if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		cube->TranslateMatrixNearAndFar(+0.1f);
	if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(-0.1f);
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(+0.1f);
	if (glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
		delete[] cube;
}

