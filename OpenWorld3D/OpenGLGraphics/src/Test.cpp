#include "Test.h"
#include "Primitive.h"
#include "Sound.h"
#include "Gui.h"
#include "Window.h"
#include "Texture.h"
#include "Terrain.h"
#include "PrimitiveObjects.h"
#include "Camera.h"

void playerInput(GLFWwindow* win, CubeObject* cube,float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
Test::Test() 
{

}

Test::~Test()
{

}

bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = static_cast<float>(1280 / 2);
float lastY = static_cast<float>(720/ 2);
float fov = 45.0f;
	
//sound
void Test::Play() const
{

	//Windows
	Window win;
	glfwSetCursorPosCallback(win.getWindowsPointer(), mouse_callback);
	win.SetInputMode();


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
		
		//Updates camera viewMatrix;
		Camera::getInstance().Update(win.deltaTime);
		//Input
		win.processInputForWindow();
		
		//Player Input
		playerInput(win.getWindowsPointer(), player, win.deltaTime);

		//Rendering commands here
		renderer.Clear();
		//Terrain & SkyBox
		terrain.Draw(&renderer);
		terrain.Update(win.deltaTime);
		//Player& Coins
		player->Draw(&renderer);
		player->Update(win.deltaTime);

		//Check objects with shaders 
		if (flagAliveForCoin) {
			coin->Draw(&renderer);
			coin->Update(win.deltaTime);
		}
		GUI.UpdateTime(&win.curTime);
		//Enemies & Score
		if (player->CheckPos(*coin)) {
			//check pos
			GUI.UpdateScore();
			flagAliveForCoin = false;
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
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
		cube->TranslateMatrixNearAndFar(-0.1f, deltaTime);
		Camera::getInstance().SetCameraPosition( Camera::getInstance().GetCameraFront(), deltaTime);
	}
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
		cube->TranslateMatrixNearAndFar(+0.1f, deltaTime);
		Camera::getInstance().SetCameraPosition(- Camera::getInstance().GetCameraFront(), deltaTime);
	}
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
		cube->TranslateMatrixLeftAndRight(-0.1f, deltaTime);
		Camera::getInstance().SetCameraPosition(-Camera::getInstance().GetCameraRight(), deltaTime);
	}
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
		cube->TranslateMatrixLeftAndRight(+0.1f, deltaTime);
		Camera::getInstance().SetCameraPosition(Camera::getInstance().GetCameraRight(), deltaTime);
	}
	//Sprint
	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cube->speed = 100.f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Camera::getInstance().SetCameraFront(glm::normalize(direction),1.f);

}