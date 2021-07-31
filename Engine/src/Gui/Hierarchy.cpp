#include "Hierarchy.h"
#include "ImGui/imgui.h"

namespace Gui
{
	void Hierarchy::SpawnWindow()
	{
		if (ImGui::Begin(wndName))
		{
			pRoot->RenderGuiTree(pSelectedNode);
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