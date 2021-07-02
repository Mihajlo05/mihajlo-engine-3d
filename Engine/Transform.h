#pragma once

#include <DirectXMath.h>

struct Transform
{
	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR rot;
	DirectX::XMVECTOR scale;
	
	Transform(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot, DirectX::XMVECTOR scale)
		: pos(pos), rot(rot), scale(scale)
	{ }
	Transform(DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f },
		DirectX::XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f },
		DirectX::XMFLOAT3 scale = {1.0f, 1.0f, 1.0f})
		:
		pos(DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f)),
		rot(DirectX::XMVectorSet(rot.x, rot.y, rot.z, 1.0f)),
		scale(DirectX::XMVectorSet(scale.x, scale.y, scale.z, 1.0f))
	{ }
	DirectX::XMMATRIX GetMatrix() const
	{
		return DirectX::XMMatrixScalingFromVector(scale) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(rot) *
			DirectX::XMMatrixTranslationFromVector(pos);
	}
};