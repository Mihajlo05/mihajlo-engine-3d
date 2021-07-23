#include "Hierarchy.h"
#include "imgui/imgui.h"

namespace Gui
{
	void Hierarchy::GenerateWindow() const
	{
		ImGui::Begin(wndName); ImGui::End();
	}

	void Hierarchy::AddEntity(Entity& e)
	{
		if (ImGui::Begin(wndName))
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

			if (ImGui::TreeNodeEx(e.GetName().c_str(), flags))
			{
				e.RenderTreeNode();
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}