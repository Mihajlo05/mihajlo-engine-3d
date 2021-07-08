#include "ControllableEntity.h"
#include "imgui/imgui.h"
#include <DirectXMath.h>

ControllableEntity::ControllableEntity(std::unique_ptr<PhongDrawable> pModel, const std::string& name, DirectX::XMFLOAT3 pos)
	:
	pModel(std::move(pModel)),
	name(name)
{
	SetLocalTransform(GetLocalTransform().Translate(pos));
}

void ControllableEntity::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	SpawnControllWindow(name);
	pModel->ResetTransformations();
	pModel->AddTransformation(GetTransfMatrix());
}

void ControllableEntity::Draw() const
{
	pModel->Draw();
}

void ControllableEntity::SpawnControllWindow(const std::string& wndName)
{
	Entity::SpawnControllWindow(wndName);

	if (ImGui::Begin(wndName.c_str()))
	{
		PhongDrawable::MaterialData md = pModel->GetMaterialData();
		float color[] = { md.materialColor.x, md.materialColor.y, md.materialColor.z };
		ImGui::Text("Boja Materijala");
		ImGui::ColorEdit3("bm", color);
		md.materialColor = { color[0], color[1], color[2] };
		ImGui::Text("Spekularni Intezitet");
		ImGui::SliderFloat("si", &md.specularIntensity, 0.0f, 5.0f);
		ImGui::Text("Spekularna Moc");
		ImGui::SliderFloat("sm", &md.specularPower, 1.0f, 150.0f);

		pModel->SetMaterialData(md);
	}
	ImGui::End();
}
