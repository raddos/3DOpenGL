#include "Test.h"
#include "Primitive.h"
#include "Object.h"
#include "Sound.h"
#include "Gui.h"

void inputs(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale);


std::pair<double, double> getCursorPosition(GLFWwindow* window);

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


		Terrain* ter = new Terrain(shaderFilepath, textureFilepath);




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



		

			//Rendering commands here
			Renderer.Clear();
			
			ter->Render();
			
			GUI.Render();

			// check and call events and swap the buffers
			win.swapBuffers();
		}
		
		GUI.Shutdown();
		win.Shutdown();
}


void inputs(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.z = -0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.z = 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x = -0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x = 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotation.z = 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotation.z = -0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		scale.x = 0.1f;
		scale.y = 0.1f;
		scale.z = 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		scale.x = 0.1f;
		scale.y = 0.1f;
		scale.z = 0.1f;
	}

}

std::pair<double,double> getCursorPosition(GLFWwindow* window) {

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return std::pair < double,double> (xpos, ypos);
}