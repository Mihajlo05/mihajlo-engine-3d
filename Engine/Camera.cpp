#include "Camera.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

void Camera::Update(float dt)
{
	if (ImGui::Begin("Kamera"))
	{
		ImGui::Text("Pozicija");
		ImGui::SliderFloat("Rastojanje", &r, 1.0f, 50.0f);
		ImGui::SliderAngle("Alfa", &alpha, -180, 180);
		ImGui::SliderAngle("Beta", &beta, -89, 89);
		ImGui::Text("Orijentacija");
		ImGui::SliderAngle("Roll", &roll, -180, 180);
		ImGui::SliderAngle("Pitch", &pitch, -180, 180);
		ImGui::SliderAngle("Yaw", &yaw, -180, 180);
	}
	ImGui::End();
}

dx::XMMATRIX Camera::GetTransfForModel() const
{
	const auto pos = dx::XMVector3Transform(
		dx::XMVectorSet(0.0f, 0.0f, -r, 0.0f),
		dx::XMMatrixRotationRollPitchYaw(beta, -alpha, 0.0f)
	);
	return dx::XMMatrixLookAtLH(
		pos, dx::XMVectorZero(),
		dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	) * dx::XMMatrixRotationRollPitchYaw(
		pitch, -yaw, roll
	);
}