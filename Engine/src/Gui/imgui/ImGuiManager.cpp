#include "ImGuiManager.h"
#include "imgui.h"

ImGuiManager::ImGuiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();
}

ImGuiManager::~ImGuiManager()
{
	ImGui::DestroyContext();
}
