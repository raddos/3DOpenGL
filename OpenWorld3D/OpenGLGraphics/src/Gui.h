#pragma once

#include "Helper/imgui/imgui.h"
#include "Helper/imgui/imgui_impl_glfw.h"
#include "Helper/imgui/imgui_impl_opengl3.h"
#include "glm/vec3.hpp"

class Gui {

	const char* glsl_version = "#version 130";
	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
public:

	void Init(GLFWwindow* window);
	virtual void Update(glm::vec3& camPosition, glm::vec3& position, bool& checked, float& rotate);
	void Render();
	void Shutdown();

};