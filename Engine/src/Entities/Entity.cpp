#include "Entity.h"
#include "imgui/imgui.h"

Transform Entity::GetLocalTransform() const
{
	return localTransf;
}

Transform Entity::GetGlobalTransform() const
{
	return globalTransf;
}

void Entity::SetLocalTransform(const Transform& t)
{
	localTransf = t;
}

void Entity::SetGlobalTransform(const Transform& t)
{
	globalTransf = t;
}

void Entity::ResetLocalTransform()
{
	localTransf = Transform();
}

void Entity::ResetGlobalTransform()
{
	globalTransf = Transform();
}

void Entity::ResetTransform()
{
	ResetLocalTransform();
	ResetGlobalTransform();
}

DirectX::XMMATRIX Entity::GetTransfMatrix() const
{
	return localTransf.GetMatrix() * globalTransf.GetMatrix();
}

void Entity::SpawnControllWindow(const std::string& wndName)
{

	Transform transform = GetLocalTransform();

	if (ImGui::Begin(wndName.c_str()))
	{
		ImGui::Text("Pozicija");

		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, transform.pos);

		ImGui::SliderFloat("X", &pos.x, -50.0f, 50.0f);
		ImGui::SliderFloat("Y", &pos.y, -50.0f, 50.0f);
		ImGui::SliderFloat("Z", &pos.z, -50.0f, 50.0f);

		transform.pos = DirectX::XMLoadFloat3(&pos);

		ImGui::Text("Orijentacija");

		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, transform.rot);

		ImGui::SliderAngle("Roll", &rot.z, -180, 180);
		ImGui::SliderAngle("Pitch", &rot.x, -89, 89);
		ImGui::SliderAngle("Yaw", &rot.y, -180, 180);

		transform.rot = DirectX::XMLoadFloat3(&rot);
		ImGui::Text("Uvecanje");

		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, transform.scale);

		ImGui::SliderFloat("sX", &scale.x, 1.0f, 20.0f);
		ImGui::SliderFloat("sY", &scale.y, 1.0f, 20.0f);
		ImGui::SliderFloat("sZ", &scale.z, 1.0f, 20.0f);

		transform.scale = DirectX::XMLoadFloat3(&scale);
	}
	ImGui::End();

	SetLocalTransform(transform);
}
