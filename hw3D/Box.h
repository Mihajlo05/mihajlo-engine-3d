#pragma once

#include "Drawable.h"
#include "AllBindables.h"
#include <memory>

class Box : public Drawable
{
public:
	Box(Graphics& gfx)
	{
		struct Vertex
		{
			struct { float x, y, z; } pos;
		};

		std::vector<Vertex> vertices =
		{
			{ 0.0f, 0.5f, 0.0f },
			{ 0.5f, -0.5f, 0.0f },
			{-0.5f, -0.5f, 0.0f}
		};

		std::vector<unsigned short> indices = { 0, 1, 2 };

		AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		AddBindable(std::make_unique<VertexBuffer>(gfx, vertices));

		AddBindable(std::make_unique<PixelShader>(gfx, L"PixelShader.cso"));

		auto pvs = std::make_unique<VertexShader>(gfx, L"VertexShader.cso");
		VertexShader& vs = *pvs;
		AddBindable(std::move(pvs));

		std::vector<D3D11_INPUT_ELEMENT_DESC> iedsc;
		iedsc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		AddBindable(std::make_unique<InputLayout>(gfx, iedsc, vs.GetBytecode(), vs.GetBytecodeSize()));

		AddBindable(std::make_unique<PrimitiveTopology>((D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)));

		D3D11_VIEWPORT dvp;
		dvp.Width = 800u;
		dvp.Height = 600u;
		dvp.MinDepth = 0.0f;
		dvp.MaxDepth = 1.0f;
		dvp.TopLeftX = 0u;
		dvp.TopLeftY = 0u;

		AddBindable(std::make_unique<Viewport>(dvp));
	}
	void Update(float dt) override {}
	DirectX::XMMATRIX GetTransformation() const
	{
		return DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	}
};