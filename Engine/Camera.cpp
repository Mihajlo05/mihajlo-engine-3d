#include "Camera.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

Camera::Camera()
	:
	GameObject(nullptr)
{ }

void Camera::Update(float dt)
{
	Rotate({ 0.0f, 0.0f, 0.0f }, {-beta, -alpha, 0.0f});
	Rotate({ -pitch, -yaw, -roll });

	if (ImGui::Begin("Kamera"))
	{
		ImGui::SliderFloat("Rastojanje", &r, 0.0f, 50.0f);
		ImGui::SliderAngle("Alfa", &alpha, -180, 180);
		ImGui::SliderAngle("Beta", &beta, -90, 90);
		ImGui::SliderAngle("Roll", &roll, -180, 180);
		ImGui::SliderAngle("Pitch", &pitch, -180, 180);
		ImGui::SliderAngle("Yaw", &yaw, -180, 180);
	}
	ImGui::End();

	SetPos({ 0.0f, 0.0f, -r });
	Rotate({ 0.0f, 0.0f, 0.0f }, { beta, alpha, 0.0f });
	Rotate({ pitch, yaw, roll });
}

void Camera::Draw() const { }

dx::XMMATRIX Camera::GetTransfForModel() const
{
	return dx::XMMatrixTranslation(-GetPos().x, -GetPos().y, -GetPos().z) *
		dx::XMMatrixRotationRollPitchYaw(-GetRotation().x, -GetRotation().y, -GetRotation().z) *
		dx::XMMatrixScaling(1.0f / GetScale().x, 1.0f / GetScale().y, 1.0f / GetScale().z);
}