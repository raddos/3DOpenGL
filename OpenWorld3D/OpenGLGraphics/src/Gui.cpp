#include "Gui.h"

void Gui::Init(GLFWwindow* window) 
{
	ImGui::CreateContext();
	IMGUI_CHECKVERSION();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
};
void Gui::Update(glm::vec3& camPosition, glm::vec3 &position,bool &checked,float &rotate)
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Game ");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Commands");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Text("Camera position on x-axis");
		ImGui::SliderFloat("kx", &camPosition.x, -6.f, 6.f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("Camera position on y-axis");
		ImGui::SliderFloat("ky", &camPosition.y, -1.f, 1.0f);

		ImGui::Text("Translate object x-axis");
		ImGui::SliderFloat("tx", &position.x, -1.f, 1.0f);
		ImGui::Text("Translate object y-axis");
		ImGui::SliderFloat("ty", &position.y, -1.f, 1.0f);
		ImGui::Text("Translate object z-axis");
		ImGui::SliderFloat("tz", &position.z, -1.f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::Checkbox("Stop rotation", &checked);
		ImGui::SameLine();
		ImGui::Text("Rotate object z-xis");

		ImGui::SliderFloat("rot", &rotate, -1.f, 1.0f);

		ImGui::Text("Rotate object x-xis");

		ImGui::SliderFloat("rot", &rotate, -1.f, 1.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
};
void Gui::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Gui::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
};