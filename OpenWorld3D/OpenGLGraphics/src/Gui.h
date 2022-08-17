#pragma once

#include "Helper/imgui/imgui.h"
#include "Helper/imgui/imgui_impl_glfw.h"
#include "Helper/imgui/imgui_impl_opengl3.h"
#include "glm/vec3.hpp"

class Gui {

	const char* glsl_version = "#version 450";
	float imGuiSizeWidth = 1000;
	float imGuiSizeHeight = 200;
	int score = 0;
	float time;
public:

	void Init(GLFWwindow* window);
	virtual void Update();
	void UpdateHealth();
	void UpdateScore();
	void UpdateTime(float* time);
	void Render();
	void Shutdown();


};

