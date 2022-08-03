#include "Window.h"
#include <iostream>
Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	this->window = glfwCreateWindow(windows_width, windows_height, title, NULL, NULL);
	if (this->window == nullptr) {
		std::cout << "Window init not working!" << std::endl;
		glfwTerminate();
	};

	glfwMakeContextCurrent(window);

	initGlad();

	setViewPort();

	printStatistcs();

	glfwSetFramebufferSizeCallback(this->window, frameBufferSizeCallBack);

};

void Window::setViewPort() {
	glViewport(0, 0, windows_width, windows_height);
}

void Window::Shutdown() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Window::initGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	};
}

void Window::printStatistcs() {
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Window::processInputForWindow()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, true);
}

int Window::getWindowsHeight() {
	return windows_height;
}
int Window:: getWindowsWidth() {
	return windows_width;
}
GLFWwindow* Window::getWindowsPointer() {
	return this->window;
}

bool Window::windowShouldClose() {
	return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->window);
}

