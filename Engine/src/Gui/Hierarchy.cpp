#include "Hierarchy.h"
#include "ImGui/imgui.h"

namespace Gui
{
	Hierarchy::Hierarchy(Graphics& gfx)
		:
		gfx(gfx),
		gizmos(gfx)
	{ }
	void Hierarchy::BeginFrame()
	{
		if (ImGui::Begin(wndName))
		{
			pRoot->RenderGuiTree(pSelectedNode);
		}
		ImGui::End();
		inspector.SpawnWindow(pSelectedNode);
		gizmos.BeginFrame();
	}

	void Hierarchy::EndFrame()
	{
		gizmos.SetNode(pSelectedNode);
		gizmos.EndFrame();
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