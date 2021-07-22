#pragma once

#include "MihajloMath.h"

struct Transform //this should be used instead of matrix when rotation and scaling should always be around origin point, not around origin point of the world
				 // aka transformation doesn't depend on order of multiplication, as it's always: scalig * roll * pitch * yaw * translation
{
	DXVec pos;
	DXVec rot;
	DXVec scale;
	
	Transform(DXVec pos, DXVec rot, DXVec scale)
		: pos(pos), rot(rot), scale(scale)
	{ }
	Transform(float3 pos = { 0.0f, 0.0f, 0.0f },
		float3 rot = { 0.0f, 0.0f, 0.0f },
		float3 scale = {1.0f, 1.0f, 1.0f})
		:
		pos(DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f)),
		rot(DirectX::XMVectorSet(rot.x, rot.y, rot.z, 1.0f)),
		scale(DirectX::XMVectorSet(scale.x, scale.y, scale.z, 1.0f))
	{ }
	matrix GetMatrix() const
	{
		return DirectX::XMMatrixScalingFromVector(scale) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(rot) *
			DirectX::XMMatrixTranslationFromVector(pos);
	}
	Transform& Translate(FDXVec delta)
	{
		pos = DirectX::XMVectorAdd(pos, delta);
		return *this;
	}
	Transform& Translate(float3 delta)
	{
		return Translate(DirectX::XMVectorSet(delta.x, delta.y, delta.z, 0.0f));
	}
	Transform& Rotate(FDXVec delta)
	{
		rot = DirectX::XMVectorAdd(rot, delta);
		return *this;
	}
	Transform& Rotate(float3 delta)
	{
		return Rotate(DirectX::XMVectorSet(delta.x, delta.y, delta.z, 0.0f));
	}
	Transform& Scale(float scalar)
	{
		scale = DirectX::XMVectorScale(scale, scalar);
		return *this;
	}
};