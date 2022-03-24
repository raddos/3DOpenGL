#include "Test.h"
#include "Primitive.h"
#include "Object.h"
#include "Sound.h"
#include "Gui.h"

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
		const char* textureFilepath = "res/textures/Texture_Dirt.jpg";
		const char* shaderFilepath = "res/shaders/cube.shader";
		Renderer Renderer;


		Terrain* ter = new Terrain(shaderFilepath, textureFilepath, 4,8);


		//Gui
		Gui GUI;
		GUI.Init(win.getWindowsPointer());
		

		while (!win.windowShouldClose())
		{

			//Update
			glfwPollEvents();
			GUI.Update();
			ter->Update();
			//Input
			win.processInputForWindow();
			//Player Input

			//Rendering commands here
			Renderer.Clear();
			//Terrain
			ter->Render();
			//Gui
			GUI.Render();
			// check and call events and swap the buffers
			win.swapBuffers();
		}
		
		GUI.Shutdown();
		win.Shutdown();
}

