#pragma once

#include "Math/IndexedTriangleList.h"
#include "Drawable.h"
#include "Bindables/PixelConstantBuffer.h"

class SolidDrawable : public Drawable
{
public:
	SolidDrawable(Graphics& gfx, IndexedTriangleList model, float3 color);
	void SetColor(float3 c);
	float3 GetColor() const;
private:
	static PixelConstantBuffer<float4>* pColorCBuf;
	float3 color;
	Graphics& gfx;
};