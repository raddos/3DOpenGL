#include "Test.h"
#include "Primitive.h"
#include "Object.h"
#include "Sound.h"
#include "Gui.h"
#include "Window.h"
#include <filesystem>

void playerInput(GLFWwindow* win, CubeObject* cube,CubeObject* cube2);

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
	Texture texture1("res/textures/TextureDirt.png");
	texture1.BindTextureSlot();
	CubeObject* cubeObject1 = new CubeObject("res/shaders/Sword.shader");
	cubeObject1->SetTexture("uniformTexture", 0);
	
	//Object 2
	Texture texture2("res/textures/SwordImage.png");
	texture2.BindTextureSlot();
	CubeObject* cubeObject2 = new CubeObject("res/shaders/Cube.shader");
	cubeObject2->SetTexture("uniformTexture", 0);
	
	//Object 3
	 Texture texture3("res/textures/TextureDirt.png");
	texture3.BindTextureSlot();
	CubeObject* cubeObject3 = new CubeObject("res/shaders/Sword.shader");
	cubeObject3->SetTexture("uniformTexture", 0);
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
	    playerInput(win.getWindowsPointer(), cubeObject1,cubeObject2);
		//Rendering commands here
		renderer->Clear();
		cubeObject1->Render(renderer);
	  	cubeObject2->Render(renderer);
		cubeObject3->Render(renderer);
		

		GUI.Render();
		win.swapBuffers();
	}

	GUI.Shutdown();
	win.Shutdown();
	return ;
}

void playerInput(GLFWwindow* win,CubeObject * cube, CubeObject* cube2) {
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
		cube->TranslateMatrixNearAndFar(-0.1f);
	}
	if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		cube->TranslateMatrixNearAndFar(+0.1f);
	if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(-0.1f);
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		cube->TranslateMatrixLeftAndRight(+0.1f);
	if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cube2->TranslateMatrixLeftAndRight(-0.05f);
	}
}

