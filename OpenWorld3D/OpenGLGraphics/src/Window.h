#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {

	int windows_width = 1280;
	int windows_height = 720;
	const char* title = "Open World 3D ";

	GLFWwindow* window;


	//delta time
	float deltatime, curtime, lasttime;

	//mouse input
	float xpos, ypos;
	float xoffset, yoffset;
	float lastxpos, lastypos;
	bool firstmouse;
public:
	Window();

	void Shutdown();

	void setViewPort();

	void initGlad();

	void printStatistcs();

	static inline void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height);}

	void processInputForWindow();

	int getWindowsHeight();

	int getWindowsWidth();

	GLFWwindow* getWindowsPointer();

	bool windowShouldClose();

	void swapBuffers();
};