#include "EditorCamera.h"
#include "EntryPoint/Application.h"

namespace dx = DirectX;

EditorCamera::EditorCamera(float aspectRation)
	:
	EditorCamera(Transform(), aspectRation)
{ }

EditorCamera::EditorCamera(Transform transf, float aspectRation)
	:
	EditorCamera(transf, dx::XMMatrixPerspectiveLH(1.0f, aspectRation, 1.0f, 100.0f))
{ }

EditorCamera::EditorCamera(Transform transf, fmatrix proj)
	:
	transf(transf),
	proj(proj)
{ }

matrix EditorCamera::GetView() const
{
	DXVec forward = dx::XMVectorSet(0, 0, 1, 1);
	DXVec up = dx::XMVectorSet(0, 1, 0, 1);

	forward = dx::XMVector3Transform(forward, dx::XMMatrixRotationRollPitchYawFromVector(transf.rot.GetDXVec()));
	DXVec toLookAt = dx::XMVector3Transform(transf.pos.GetDXVec(), dx::XMMatrixTranslationFromVector(forward));

	return dx::XMMatrixLookAtLH(transf.pos.GetDXVec(), toLookAt, up);
}

matrix EditorCamera::GetProjection() const
{
	return proj;
}

matrix EditorCamera::GetViewProjection() const
{
	return GetView() * GetProjection();
}

void EditorCamera::SetProjection(fmatrix proj)
{
	this->proj = proj;
}

Transform EditorCamera::GetTransform() const
{
	return transf;
}

void EditorCamera::SetTransform(const Transform& transf)
{
	this->transf = transf;
}

void EditorCamera::HandleMouseInput(const Mouse::Event& e)
{
	if (!e.IsRawDelta()) return;

	float dx = (float)e.GetX();
	float dy = (float)e.GetY();
	float dt = Application::GetDeltaTime();

	transf.Rotate(float3{ rotSpeed * dy * dt, rotSpeed * dx * dt, 0.0f });
	transf.WrapRotation();
	transf.ClampPitch();
}

void EditorCamera::Update(float dt, Keyboard& kbd)
{
	DXVec delta = dx::XMVectorSet(0, 0, 0, 1);

	if (kbd.IsKeyPressed('W')) delta = dx::XMVector3Transform(delta, dx::XMMatrixTranslation(0, 0, 1));
	if (kbd.IsKeyPressed('S')) delta = dx::XMVector3Transform(delta, dx::XMMatrixTranslation(0, 0, -1));
	if (kbd.IsKeyPressed('A')) delta = dx::XMVector3Transform(delta, dx::XMMatrixTranslation(-1, 0, 0));
	if (kbd.IsKeyPressed('D')) delta = dx::XMVector3Transform(delta, dx::XMMatrixTranslation(1, 0, 0));

	delta = dx::XMVector3Transform(delta, dx::XMMatrixRotationRollPitchYawFromVector(transf.rot) *
		dx::XMMatrixScaling(travelSpeed * dt, travelSpeed * dt, travelSpeed * dt));
	transf.Translate(delta);
}
