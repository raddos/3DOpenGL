#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {

	int windows_width = 1280;
	int windows_height = 720;
	const char* title = "Open World 3D ";

	GLFWwindow* window;

public:
	Window();

	void Shutdown();

	void setViewPort() {
		//viewport where we render pixels in window
		glViewport(0, 0, windows_width, windows_height);
	}

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