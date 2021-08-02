#pragma once
#include <math.h>
#include <cmath>
#include  <DirectXMath.h>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;
constexpr float deg2rad = PI / 180.0f;
constexpr float rad2deg = 180.0f / PI;

using float2 = DirectX::XMFLOAT2;
using float3 = DirectX::XMFLOAT3;
using float4 = DirectX::XMFLOAT4;
using float3x3 = DirectX::XMFLOAT3X3;
using float4x4 = DirectX::XMFLOAT4X4;
using matrix = DirectX::XMMATRIX;
using fmatrix = DirectX::FXMMATRIX;
using DXVec = DirectX::XMVECTOR;
using FDXVec = DirectX::FXMVECTOR;

template <typename T>
constexpr auto sq(const T& x)
{
	return x * x;
}

template<typename T>
T WrapAngle(T theta)
{
	constexpr T twoPi = (T)2 * (T)PI_D;
	const T mod = (T)fmod(theta, twoPi);
	if (mod > (T)PI_D)
	{
		return mod - twoPi;
	}
	else if (mod < -(T)PI_D)
	{
		return mod + twoPi;
	}
	return mod;
}

template<typename T>
T Clamp(T val, T min, T max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

template<typename T>
constexpr T Interpolate(const T& src, const T& dst, float alpha)
{
	return src + (dst - src) * alpha;
}

template<typename T>
constexpr T ToRad(T deg)
{
	return deg * PI / (T)180.0;
}