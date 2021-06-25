#pragma once

#include "DrawableBase.h"
#include "IndexedTriangleList.h"
#include "DefaultVertex.h"
#include <memory>
#include "AllBindables.h"

class FlatDrawable : public DrawableBase<FlatDrawable>
{
public:
	template<class Vertex>
	FlatDrawable(Graphics& gfx, IndexedTriangleList<Vertex> indTriangleL)
	{
		if (!IsStaticInitialized())
		{
			AddStaticBindable(std::make_unique<VertexBuffer>(gfx, indTriangleL.Vertices()));
			AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indTriangleL.Indices()));

			AddStaticBindable(std::make_unique<PrimitiveTopology>(indTriangleL.GetType()));

			struct PCBuf
			{
				struct { float r, g, b, a; } color[6];
			};

			const PCBuf pcbuf =
			{
				{
					{1.0f, 1.0f, 1.0f, 1.0f},
					{1.0f, 1.0f, 0.0f, 1.0f},
					{1.0f, 0.0f, 1.0f, 1.0f},
					{0.0f, 1.0f, 1.0f, 1.0f},
					{0.0f, 0.0f, 1.0f, 1.0f},
					{0.0f, 1.0f, 0.0f, 1.0f}
				}
			};

			AddStaticBindable(std::make_unique<PixelConstantBuffer<PCBuf>>(gfx, pcbuf));

			AddStaticBindable(std::make_unique<PixelShader>(gfx, L"FlatPixelShader.cso"));

			std::unique_ptr<VertexShader> upVertexShader = std::make_unique<VertexShader>(gfx, L"FlatVertexShader.cso");
			VertexShader* pVertexShader = upVertexShader.get();
			AddStaticBindable(std::move(upVertexShader));

			std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};
			AddStaticBindable(std::make_unique<InputLayout>(gfx, ied, pVertexShader->GetBytecode(), pVertexShader->GetBytecodeSize()));
		}
		else
		{
			AddIndexBufferFromStatic();
		}

		AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, static_cast<const Drawable&>(*this)));
	}
	void UpdateLogic(float dt) override
	{
		time += dt;
	}
	void UpdateGraphics(Graphics& gfx) override
	{
	}
	DirectX::XMMATRIX GetTransformation() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(time, time * 2, time / 2) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	}
private:
	float time = 0.0f;
};