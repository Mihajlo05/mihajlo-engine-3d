#pragma once

#include "DrawableBase.h"
#include "Math/IndexedTriangleList.h"
#include <DirectXMath.h>

class PhongDrawable : public DrawableBase<PhongDrawable>
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
	};
	struct MaterialData
	{
		DirectX::XMFLOAT3 materialColor;
		float phongIntensity;
		float phongPower;
		float padding[3];
	};
public:
	PhongDrawable(Graphics& gfx, IndexedTriangleList<Vertex> model, const MaterialData& mData);
	virtual ~PhongDrawable() = default;
private:
	MaterialData mData;
};