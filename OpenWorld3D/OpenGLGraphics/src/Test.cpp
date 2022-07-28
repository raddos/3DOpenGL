#include "Test.h"
#include "Primitive.h"
#include "Object.h"
#include "Sound.h"
#include "Gui.h"
#include "Window.h"
#include <filesystem>

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
	Renderer* renderer = new Renderer();



	//sound
	Sound s;
	s.testSound();



	//Object 1 
	Texture tex("res/textures/Te.png");
	tex.BindTextureSlot();
	CubeObject* cubeObject = new CubeObject("res/shaders/Cube.shader");
	cubeObject->SetTexture("uniformTexture", 0);
	//Object 2
	Texture texture2("res/textures/SwordImage.png");
	texture2.BindTextureSlot();
	CubeObject* cubeObject2 = new CubeObject("res/shaders/Sword.shader");
	cubeObject2->SetTexture("SwordUniformTexture",1);
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
	    playerInput(win.getWindowsPointer(), cubeObject);
		//Rendering commands here
		renderer->Clear();
		cubeObject->Render(renderer);
	  	cubeObject2->Render(renderer);
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
}

