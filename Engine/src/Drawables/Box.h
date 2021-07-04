#pragma once

#include "DrawableBase.h"
#include "Graphics/Graphics.h"
#include "Math/IndexedTriangleList.h"
#include "Models/CubeModel.h"

class Box : public DrawableBase<Box>
{
private:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
	};
public:
	Box(Graphics& gfx);
};