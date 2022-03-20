#include "IncludeAll.h"
#include <glm/gtc/type_ptr.hpp>
#include "Primitive.h"

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

		
		//VAO ( Vertex array object) - > container for VBO and EBO 
		VertexArray va;
		
		Primitive* q = new Cube();
		//VBO ( Vertex buffer object)  - > container for buffer data ( vertices , floats , positions , color , textures ) 
		VertexBuffer vb(q->getNumberOfVertices(),q->getVertices());

		// Pointing vertex atribbutes pointers to specific data ( telling shaders how to operate memory)
		va.AddBuffer(vb);
	

		// indexing data of vertecises ( optimazing data )
		IndexBuffer ib(q->getNumberOfIndices(), q->getIndices());

		// making shader program
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		
		// setting uniform of fragment shader to points
		shader.SetUniform4f("uniformColor", 0.8f, 0.3f, 0.4f, 1.0f);


		// Attributes
		glm::vec3 position(0.f);
		glm::vec3 refposition(0.f);
		glm::vec3 rotation(0.f);
		glm::vec3 scale(1.f);
		//setting matrix ( INNIT )
		// Indentity matrix needed for manipulation
		glm::mat4 modelMatrix(1.f);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f,0.0f,0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMatrix = glm::scale(modelMatrix, scale);
 

	//	glm::mat4 proj = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f); // orthogonal projection
	//	shader.SetUniformMat4f("u_MatrixViewProjection", proj);
		
		// View - camera 
		glm::mat4 ViewMatrix(1.f);
		glm::vec3 camPosition(0.f, 0.0f, 1.f);
		glm::vec3 lookUpWorld(0.f, 1.0f, 0.0f);
		glm::vec3 camFront(0.0f, 0.0,-1.f);
		ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, lookUpWorld);

		// Projection perspective form point of origine - camera
		glm::mat4 perspectiveProj(1.0f);
		float FOV = 90.f;
		float nearPlane = 0.1f;
		float farPlane = 1000.f;
		perspectiveProj = glm::perspective(glm::radians(FOV), static_cast<float>(win.getWindowsWidth()) / win.getWindowsHeight(), nearPlane, farPlane);

		shader.SetUniformMat4f("u_ModelMatrix", modelMatrix);
		shader.SetUniformMat4f("u_ViewMatrix", ViewMatrix);
		shader.SetUniformMat4f("u_PerspectiveProjection", perspectiveProj);

		//Light
		glm::vec3 lightPos(0.f, 0.f, 2.f);


		shader.SetUniform3fv("lightPos", glm::value_ptr(lightPos));
		shader.SetUniform3fv("camPosition", glm::value_ptr(camPosition));

		//setting specifiy dexture 
		Texture texture("res/textures/Texture_Dirt.jpg");
		texture.Bind();
		shader.SetUniform1i("uniformTexture", 0);
		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
		//render loop

		Renderer renderer;

		//Gui
		Gui GUI;
		GUI.Init(win.getWindowsPointer());


		while (!win.windowShouldClose())
		{

			//Update
			glfwPollEvents();
			inputs(win.getWindowsPointer(), position, rotation, scale);

			static bool checked = false;
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			modelMatrix = glm::scale(modelMatrix, scale);
			//modelMatrix = glm::rotate(modelMatrix, glm::radians(5.f), glm::vec3(0.0f, 1.0f, 0.0f));

			//Input
			win.processInputForWindow();
			//Player Input

			//Rendering commands here
			renderer.Clear();
			

			shader.Bind();
			shader.SetUniform4f("uniformColor", 0.1f, 0.3f, 0.8f, 1.0f);

			float rotate = 0.0f;
			
			shader.SetUniformMat4f("u_ModelMatrix", modelMatrix);
		
			// Drawing
			renderer.Draw(va, ib, shader);
			
			GUI.Update(camPosition, position, checked, rotate);

			std::pair<double,double> p = getCursorPosition(win.getWindowsPointer());
			camPosition = glm::vec3((float)p.first, (float)p.second, camPosition.z);
			ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, lookUpWorld);
			shader.SetUniformMat4f("u_ViewMatrix", ViewMatrix);
			modelMatrix = glm::translate(modelMatrix, position);
			if (checked) 
				modelMatrix = glm::rotate(modelMatrix, glm::radians(-5.f), glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotate), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::translate(modelMatrix, refposition);
			shader.SetUniformMat4f("u_ModelMatrix", modelMatrix);

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