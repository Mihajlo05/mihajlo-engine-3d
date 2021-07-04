#pragma once

#include "Entity.h"
#include "Graphics/Color.h"
#include "Drawables/SolidSphere.h"
#include "Bindables/PixelConstantBuffer.h"

class PointLight : public Entity
{
public:
	PointLight(Color c, Graphics& gfx);
	void Bind(Graphics& gfx, DirectX::XMMATRIX view) const;
	void Draw() const override;
private:
	struct CBufData
	{
		DirectX::XMFLOAT3 pos;
		float padding;
	};
private:
	Color color;
	mutable SolidSphere model;
	mutable PixelConstantBuffer<CBufData> cbuf;
};
