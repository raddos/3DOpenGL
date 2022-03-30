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
	const char* textureFilepath = "res/textures/Texture_Dirt.jpg";
	const char* textureFilepathPlayer = "res/textures/PunyKnight.png";
	const char* shaderFilepathForTerrain = "res/shaders/cube.shader";
	const char* shaderFilepathForPlayer = "res/shaders/player.shader";
	Renderer* renderer = new Renderer();

	Texture tex(textureFilepathPlayer);
	//Texture for terrain

	Texture tx(textureFilepath);
	tx.BindTextureSlot();


	Terrain* ter = new Terrain(shaderFilepathForTerrain, 12,12);

	CubeObject* player = new CubeObject(shaderFilepathForPlayer);
	player->setPlayer();

	Primitive* p = new Circle();

	VertexArray vao;
	VertexBuffer vb(p->getNumberOfVertices(), p->getVertices());
	vao.AddBuffer(vb);
	IndexBuffer ib(p->getNumberOfIndices(), p->getIndices());

	//Gui
	Gui GUI;
	GUI.Init(win.getWindowsPointer());


	while (!win.windowShouldClose())
	{

		//Update
		glfwPollEvents();
		GUI.Update();
		ter->Update();
		player->Update();
		//Input
		win.processInputForWindow();
		//Player Input
		playerInput(win.getWindowsPointer(), player);
		//Rendering commands here
		renderer->Clear();
		//Terrain
		ter->Render(renderer);
		player->Render(renderer);
		renderer->Draw(vao,ib,Shader(shaderFilepathForTerrain));
		//Gui
		GUI.Render();
		// check and call events and swap the buffers
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

