#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {

	int windows_width = 1280;
	int windows_height = 720;
	const char* title = "Open World 3D ";

	GLFWwindow* window;

public:
	//delta time
	float deltaTime, curTime, lastTime;
	//mouse input
	float yaw;
	float pitch;
	float lastx, lasty;
	bool firstmouse;
	
	Window();

	void Shutdown();

	void setViewPort();

	void initGlad();

	void printStatistcs();

	static inline void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);}
	void processInputForWindow();

	int getWindowsHeight();

	int getWindowsWidth();
	inline void SetInputMode(){ glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

	GLFWwindow* getWindowsPointer();

	bool windowShouldClose();

	void swapBuffers();
};