#pragma once

#include "Math/IndexedTriangleList.h"
#include "Drawable.h"
#include "Bindables/PixelConstantBuffer.h"

namespace Drawables
{
	class Solid : public Drawable
	{
	public:
		Solid(Graphics& gfx, IndexedTriangleList model, float3 color);
		void SetColor(float3 c);
		float3 GetColor() const;
	private:
		static PixelConstantBuffer<float4>* pColorCBuf;
		float3 color;
		Graphics& gfx;
	};
}