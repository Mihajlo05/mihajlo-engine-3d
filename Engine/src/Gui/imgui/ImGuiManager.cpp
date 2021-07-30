#include "ImGuiManager.h"
#include "imgui.h"

ImGuiManager::ImGuiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
}

ImGuiManager::~ImGuiManager()
{
	ImGui::DestroyContext();
}
