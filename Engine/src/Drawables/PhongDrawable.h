#pragma once

#include "DrawableBase.h"
#include "Math/IndexedTriangleList.h"
#include <DirectXMath.h>
#include "Bindables/PixelConstantBuffer.h"

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
		float specularIntensity;
		float specularPower;
		float padding[3];
	};
public:
	PhongDrawable(Graphics& gfx, IndexedTriangleList<Vertex> model, const MaterialData& mData);
	MaterialData GetMaterialData() const;
	void SetMaterialData(const MaterialData& mData);
	virtual ~PhongDrawable() = default;
private:
	MaterialData mData;
	PixelConstantBuffer<MaterialData>* pPixelConstantBuffer = nullptr;
};