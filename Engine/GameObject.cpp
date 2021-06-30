#include "GameObject.h"

void GameObject::Update(float dt)
{
	model->ResetTransformations();
	model->AddTransformation(DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
	model->Update(dt);
}

void GameObject::Draw() const
{
	model->Draw();
}

void GameObject::Translate(DirectX::XMFLOAT3 delta)
{
	AddToTransformation(pos, delta);
}

void GameObject::Rotate(DirectX::XMFLOAT3 delta)
{
	AddToTransformation(rotation, delta);
}

void GameObject::Rotate(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 delta)
{
	Rotate(delta);
	auto vPos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	auto dVec = DirectX::XMVectorSubtract(vPos, DirectX::XMVectorSet(center.x, center.y, center.z, 1.0f));
	auto dVec2 = DirectX::XMVector3Transform(dVec, DirectX::XMMatrixRotationRollPitchYaw(delta.x, delta.y, delta.z));
	DirectX::XMStoreFloat3(&pos, DirectX::XMVectorAdd(vPos, DirectX::XMVectorSubtract(dVec2, dVec)));
}

void GameObject::Scale(DirectX::XMFLOAT3 delta)
{
	AddToTransformation(scale, delta);
}

DirectX::XMFLOAT3 GameObject::GetPos() const
{
	return pos;
}

DirectX::XMFLOAT3 GameObject::GetRotation() const
{
	return rotation;
}

DirectX::XMFLOAT3 GameObject::GetScale() const
{
	return scale;
}

void GameObject::SetPos(DirectX::XMFLOAT3 p)
{
	pos = p;
}

GameObject::GameObject(std::unique_ptr<Drawable> model)
	:
	model(std::move(model))
{ }

void GameObject::AddToTransformation(DirectX::XMFLOAT3& t, DirectX::XMFLOAT3 delta)
{
	auto vec = DirectX::XMVectorSet(t.x, t.y, t.z, 1.0f);
	DirectX::XMStoreFloat3(&t, DirectX::XMVectorAdd(vec, DirectX::XMVectorSet(delta.x, delta.y, delta.z, 1.0f)));
}
