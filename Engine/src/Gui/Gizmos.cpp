#include "Gizmos.h"
#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

namespace Gui
{
	Gizmos::Gizmos(Graphics& gfx)
		:
		gfx(gfx)
	{ }

	void Gizmos::SetNode(Node* pn)
	{
		pNode = pn;
	}

	void Gizmos::BeginFrame()
	{
		ImGuizmo::BeginFrame();
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::Button("T"))
				operation = (int)ImGuizmo::OPERATION::TRANSLATE;
			else if (ImGui::Button("R"))
				operation = (int)ImGuizmo::OPERATION::ROTATE;
			else if (ImGui::Button("S"))
				operation = (int)ImGuizmo::OPERATION::SCALE;
		}
		ImGui::EndMainMenuBar();
	}

	void Gizmos::EndFrame()
	{
		if (!pNode) return;

		ImGuizmo::SetOrthographic(false);
		float2 rpos = gfx.GetRendererPos();
		float2 rsize = gfx.GetRendererSize();
		ImGuizmo::SetRect(rpos.x, rpos.y, rsize.x, rsize.y);

		Vector oldRot = pNode->GetTransform().rot;
		matrix view = gfx.GetCamera().GetView();
		matrix proj = gfx.GetCamera().GetProjection();
		matrix transf = pNode->GetTransform().GetMatrix();

		auto cast = [](matrix& m)
		{
			return reinterpret_cast<float*>(&m);
		};

		ImGuizmo::Manipulate(cast(view), cast(proj), ImGuizmo::OPERATION(operation), ImGuizmo::MODE::LOCAL, cast(transf));

		if (ImGuizmo::IsUsing())
		{
			Transform manipulatedTransf = transf;
			Transform nodeTransf = pNode->GetTransform();

			Vector deltaRot = manipulatedTransf.rot - nodeTransf.rot;

			nodeTransf.pos = manipulatedTransf.pos;
			nodeTransf.rot += deltaRot; //to fix gimbal lock problem
			nodeTransf.scale = manipulatedTransf.scale;
			nodeTransf.WrapRotation();

			pNode->SetTransform(nodeTransf);
		}
	}

}