#include "Hierarchy.h"
#include "ImGui/imgui.h"
#include "Gui/ImGuizmo/ImGuizmo.h"

namespace Gui
{
	void Hierarchy::BeginFrame()
	{
		ImGuizmo::BeginFrame();

		if (ImGui::Begin(wndName))
		{
			pRoot->RenderGuiTree(pSelectedNode);
		}
		ImGui::End();
		inspector.SpawnWindow(pSelectedNode);
	}

	void Hierarchy::EndFrame(float2 rndPos, float2 rndSize, ICamera& cam)
	{
		Node* pNode = Gui::Hierarchy::Get().GetSelectedNode();

		if (pNode)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(rndPos.x, rndPos.y, rndSize.x, rndSize.y);

			matrix proj = cam.GetProjection();
			matrix view = cam.GetView();
			matrix transf = pNode->GetTransform().GetMatrix();

			float* p = reinterpret_cast<float*>(&proj);
			float* v = reinterpret_cast<float*>(&view);
			float* t = reinterpret_cast<float*>(&transf);

			ImGuizmo::Manipulate(v, p, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, t);

			pNode->SetTransform(transf);
		}
	}

	void Hierarchy::SetRoot(Node& node)
	{
		pRoot = &node;
	}

	const Node* Hierarchy::GetRoot() const
	{
		return pRoot;
	}
	Node* Hierarchy::GetSelectedNode()
	{
		return pSelectedNode;
	}
	const Node* Hierarchy::GetSelectedNode() const
	{
		return pSelectedNode;
	}
}