#pragma once

#include "Entity.h"
#include "Graphics/Color.h"
#include "Drawables/SolidSphere.h"
#include "Bindables/PixelConstantBuffer.h"

class PointLight : public Entity
{
public:
	struct Desc
	{
		Color ambient;
		Color diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	struct CBufData
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
public:
	PointLight(DirectX::XMVECTOR pos, Desc desc, Graphics& gfx);
	void Bind(Graphics& gfx, DirectX::XMMATRIX view) const;
	void Draw() const override;
private:
	Color ambient;
	Color diffuseColor;
	float diffuseIntensity;
	float attConst;
	float attLin;
	float attQuad;
	mutable SolidSphere model;
	mutable PixelConstantBuffer<CBufData> cbuf;
};
