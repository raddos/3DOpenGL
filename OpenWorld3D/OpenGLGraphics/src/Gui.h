#pragma once

#include "Helper/imgui/imgui.h"
#include "Helper/imgui/imgui_impl_glfw.h"
#include "Helper/imgui/imgui_impl_opengl3.h"
#include "glm/vec3.hpp"

class Gui {

	const char* glsl_version = "#version 130";
	float imGuiSizeWidth = 1000;
	float imGuiSizeHeight = 200;
    float score;
	float health;
	float time;
public:

	void Init(GLFWwindow* window);
	virtual void Update();
	void UpdateScore();
	void Render();
	void Shutdown();


};

