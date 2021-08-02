#pragma once

#include "MihajloMath.h"

class Vector
{
public:
	Vector()
		:
		data(DirectX::XMVectorSet(0, 0, 0, 0))
	{ }
	Vector(float4 f4) : data(DirectX::XMLoadFloat4(&f4)) { }
	Vector(float3 f3) : data(DirectX::XMLoadFloat3(&f3)) { }
	Vector(float2 f2) : data(DirectX::XMLoadFloat2(&f2)) { }
	Vector(float x, float y, float z, float w) : Vector(float4{ x, y, z, w }) { }
	Vector(float x, float y, float z) : Vector(float3{ x, y, z }) { }
	Vector(float x, float y) : Vector(float2{ x, y }) { }
	Vector(DXVec dxVec) : data(dxVec) { }
	float4 GetFloat4() const
	{
		float4 f4;
		DirectX::XMStoreFloat4(&f4, data);
		return f4;
	}
	float3 GetFloat3() const
	{
		float3 f3;
		DirectX::XMStoreFloat3(&f3, data);
		return f3;
	}
	float2 GetFloat2() const
	{
		float2 f2;
		DirectX::XMStoreFloat2(&f2, data);
		return f2;
	}
	DXVec& GetDXVec()
	{
		return data;
	}
	const DXVec& GetDXVec() const
	{
		return data;
	}
	float GetX() const
	{
		return DirectX::XMVectorGetX(data);
	}
	float GetY() const
	{
		return DirectX::XMVectorGetY(data);
	}
	float GetZ() const
	{
		return DirectX::XMVectorGetZ(data);
	}
	float GetW() const
	{
		return DirectX::XMVectorGetW(data);
	}
	float GetByIndex(size_t i) const
	{
		return DirectX::XMVectorGetByIndex(data, i);
	}
	Vector& SetX(float v)
	{
		data = DirectX::XMVectorSetX(data, v);
		return *this;
	}
	Vector& SetY(float v)
	{
		data = DirectX::XMVectorSetY(data, v);
		return *this;
	}
	Vector& SetZ(float v)
	{
		data = DirectX::XMVectorSetZ(data, v);
		return *this;
	}
	Vector& SetW(float v)
	{
		data = DirectX::XMVectorSetW(data, v);
		return *this;
	}
	Vector& SetByIndex(float v, size_t i)
	{
		data = DirectX::XMVectorSetByIndex(data, v, i);
		return *this;
	}
	bool operator==(const Vector& rhs) const
	{
		float4 f = GetFloat4();
		float4 rf = rhs.GetFloat4();
		return f.x == rf.x && f.y == rf.y && f.z == rf.z && f.w == rf.w;
	}
	Vector operator+(const Vector& rhs) const
	{
		return DirectX::XMVectorAdd(data, rhs.data);
	}
	Vector& operator+=(const Vector& rhs)
	{
		return *this = *this + rhs;
	}
	Vector operator-(const Vector& rhs) const
	{
		return DirectX::XMVectorSubtract(data, rhs.data);
	}
	Vector& operator-=(const Vector& rhs)
	{
		return *this = *this - rhs;
	}
	Vector operator*(const Vector& rhs) const
	{
		return DirectX::XMVector3Dot(data, rhs.data);
	}
	Vector operator*(float scalar) const
	{
		return DirectX::XMVectorScale(data, scalar);
	}
	Vector& operator*=(float scalar)
	{
		return *this = *this * scalar;
	}
	Vector& Transform(fmatrix t)
	{
		data = DirectX::XMVector3Transform(data, t);
		return *this;
	}
	Vector GetNormalized() const
	{
		return DirectX::XMVector3Normalize(data);
	}
private:
	DXVec data;
};

inline Vector Hadamard(const Vector& lhs, const Vector& rhs)
{
	float4 lf = lhs.GetFloat4();
	float4 rf = rhs.GetFloat4();
	return { lf.x * rf.x, lf.y * rf.y, lf.z * rf.z, lf.w * rf.w };
}
