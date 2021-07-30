#pragma once

#include "MihajloMath.h"

class Vector
{
public:
	Vector()
		:
		data(DirectX::XMVectorSet(0, 0, 0, 0))
	{ }
	Vector(float4 f4) : Vector(DirectX::XMLoadFloat4(&f4)) { }
	Vector(float3 f3) : Vector(DirectX::XMLoadFloat3(&f3)) { }
	Vector(float x, float y, float z, float w) : Vector(float4{ x, y, z, w }) {}
	Vector(float x, float y, float z) : Vector(float3{ x, y, z }) {}
	Vector(DXVec dxVec) : data(dxVec) { }
	operator DXVec()
	{
		return data;
	}
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
	operator float4()
	{
		return GetFloat4();
	}
	operator float3()
	{
		return GetFloat3();
	}
	operator float2()
	{
		return GetFloat2();
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
		return GetFloat4().x;
	}
	float GetY() const
	{
		return GetFloat4().y;
	}
	float GetZ() const
	{
		return GetFloat4().z;
	}
	float GetW() const
	{
		return GetFloat4().w;
	}
	Vector& SetX(float v)
	{
		float4 f = GetFloat4();
		f.x = v;
		return *this = f;
	}
	Vector& SetY(float v)
	{
		float4 f = GetFloat4();
		f.y = v;
		return *this = f;
	}
	Vector& SetZ(float v)
	{
		float4 f = GetFloat4();
		f.z = v;
		return *this = f;
	}
	Vector& SetW(float v)
	{
		float4 f = GetFloat4();
		f.w = v;
		return *this = f;
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
	Vector& Scale(float v)
	{
		data = DirectX::XMVectorScale(data, v);
		return *this;
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
