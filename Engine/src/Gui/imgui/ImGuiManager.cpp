#include "ImGuiManager.h"
#include "imgui.h"
#include "Gui/ImGuizmo/ImGuizmo.h"

ImGuiManager::ImGuiManager()
{
	IMGUI_CHECKVERSION();
	ImGuiContext* pContext = ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGuizmo::SetImGuiContext(pContext);
}

ImGuiManager::~ImGuiManager()
{
	ImGui::DestroyContext();
}
