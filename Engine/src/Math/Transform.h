#pragma once

#include "MihajloMath.h"
#include "Vector.h"

struct Transform //this should be used instead of matrix when rotation and scaling should always be around origin point, not around origin point of the world
				 // aka transformation doesn't depend on order of multiplication, as it's always: scalig * roll * pitch * yaw * translation
{
	Vector pos;
	Vector rot;
	Vector scale;
	
	Transform(const Vector& pos = {0, 0, 0},
		const Vector& rot = {0, 0, 0},
		const Vector& scale = {1, 1, 1})
		:
		pos(pos),
		rot(rot),
		scale(scale)
	{ }
	Transform(fmatrix t)
	{
		DirectX::XMMatrixDecompose(&scale.GetDXVec(), &rot.GetDXVec(), &pos.GetDXVec(), t);
		float angle = 0.0f;
		DirectX::XMQuaternionToAxisAngle(&rot.GetDXVec(), &angle, rot);
		rot.Scale(angle);
	}
	matrix GetMatrix() const
	{
		return DirectX::XMMatrixScalingFromVector(scale.GetDXVec()) *
			DirectX::XMMatrixRotationRollPitchYawFromVector(rot.GetDXVec()) *
			DirectX::XMMatrixTranslationFromVector(pos.GetDXVec());
	}
	operator matrix()
	{
		return GetMatrix();
	}
	Transform& Translate(Vector delta)
	{
		pos += delta;
		return *this;
	}
	Transform& Translate(float x, float y, float z)
	{
		return Translate({ x, y, z });
	}
	Transform& Rotate(Vector delta)
	{
		rot += delta;
		return *this;
	}
	Transform& Rotate(float pitch, float yaw, float roll)
	{
		return Rotate({ pitch, yaw, roll });
	}
	Transform& Scale(Vector delta)
	{
		scale = Hadamard(scale, delta);
		return *this;
	}
	Transform& Scale(float x, float y, float z)
	{
		return Scale({ x, y, z });
	}
	Transform& Scale(float scalar)
	{
		scale.Scale(scalar);
		return *this;
	}
	Transform& WrapRotation()
	{
		float3 r = rot.GetFloat3();

		r.x = WrapAngle(r.x);
		r.y = WrapAngle(r.y);
		r.z = WrapAngle(r.z);

		rot = DirectX::XMLoadFloat3(&r);

		return *this;
	}
	Transform& ClampPitch()
	{
		float3 r = rot.GetFloat3();

		float deg = 0.99f * (PI / 2.0f);

		r.x = Clamp(r.x, -deg, deg);

		rot = r;

		return *this;
	}
};