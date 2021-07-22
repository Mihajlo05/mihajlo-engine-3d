#include "Entity.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

Entity::Entity(const std::string& name)
	:
	name(name)
{ }

Transform Entity::GetTransform() const
{
	return transf;
}

void Entity::SetTransform(const Transform& transf)
{
	this->transf = transf;
}

void Entity::SpawnControllWindow()
{
	if (ImGui::Begin(name.c_str()))
	{
		float3 pos;
		dx::XMStoreFloat3(&pos, transf.pos);

		ImGui::InputFloat3("Pozicija", &pos.x);

		transf.pos = dx::XMLoadFloat3(&pos);

		ImGui::Text("Orijentacija");

		float3 rot;
		dx::XMStoreFloat3(&rot, transf.rot);

		ImGui::SliderAngle("Roll", &rot.z, -180, 180);
		ImGui::SliderAngle("Pitch", &rot.x, -180, 180);
		ImGui::SliderAngle("Yaw", &rot.y, -180, 180);

		transf.rot = dx::XMLoadFloat3(&rot);
	}
	ImGui::End();
}

std::string Entity::GetName() const
{
	return name;
}

void Entity::SetName(const std::string& name)
{
	this->name = name;
}
