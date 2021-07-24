#include "Inspector.h"
#include "imgui/imgui.h"

namespace Gui
{
	void Inspector::SpawnWindow(Node* pNode)
	{
		if (ImGui::Begin(wndName))
		{
			if (pNode != nullptr)
			{
				pNode->ShowOnInspector();
			}
		}
		ImGui::End();
	}
}