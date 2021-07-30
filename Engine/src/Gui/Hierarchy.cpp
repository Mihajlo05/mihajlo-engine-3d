#include "Hierarchy.h"
#include "ImGui/imgui.h"

namespace Gui
{
	void Hierarchy::SpawnWindow()
	{
		if (ImGui::Begin(wndName))
		{
			int nodeIndexTracker = 0;
			static std::optional<int> selectedIndex;
			pRoot->RenderGuiTree(nodeIndexTracker, selectedIndex, pSelectedNode);
		}
		ImGui::End();
		inspector.SpawnWindow(pSelectedNode);
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