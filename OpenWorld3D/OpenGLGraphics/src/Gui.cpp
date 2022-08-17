#include "Gui.h"

void Colors()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(50, 16, 16, 50);
	style.Colors[ImGuiCol_Border] = ImColor(20, 20, 1, 50);

};

void Gui::Init(GLFWwindow* window) 
{
	this->score = 0;
	ImGui::CreateContext();
	IMGUI_CHECKVERSION();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	Colors();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
};
void Gui::Update()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		int health = 10;
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Begin("Game",0,ImGuiWindowFlags_NoTitleBar);                          // Create a window called "Hello, world!" and append into it.
		ImGui::SetWindowSize(ImVec2((float)imGuiSizeWidth, (float)imGuiSizeHeight));
		ImGui::SetWindowFontScale(3.2f);
		ImGui::SetWindowPos(ImVec2(0, 0));

		ImGui::Text("Game");               // Display some text (you can use a format strings too)
		
		ImGui::Text("Health: %d",health);
		ImGui::Text("Score: %d", score);
		ImGui::Text("Time: %0.2f",time);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::End();
	}
};

void Gui::UpdateScore()
{
	this->score++;
}

void Gui::UpdateTime(float* time) {
	this->time = *time;

}

void Gui::UpdateHealth() {

}
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
