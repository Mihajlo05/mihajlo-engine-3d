#include "Hierarchy.h"
#include "imgui/imgui.h"

namespace Gui
{
	void Hierarchy::SpawnWindow() const
	{
		if (ImGui::Begin(wndName))
		{
			pRoot->RenderGuiTree();
		}
		ImGui::End();
	}

	void Hierarchy::SetRoot(Node& node)
	{
		pRoot = &node;
	}

	const Node* Hierarchy::GetRoot() const
	{
		return pRoot;
	}
}