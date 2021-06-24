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
			{ -1.0f,-1.0f,-1.0f	 },
			{ 1.0f,-1.0f,-1.0f	 },
			{ -1.0f,1.0f,-1.0f	 },
			{ 1.0f,1.0f,-1.0f	  },
			{ -1.0f,-1.0f,1.0f	 },
			{ 1.0f,-1.0f,1.0f	  },
			{ -1.0f,1.0f,1.0f	 },
			{ 1.0f,1.0f,1.0f	 }
		};

		std::vector<unsigned short> indices = {
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
		};

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

		AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));

		struct PSCBuf
		{
			struct
			{
				float r, g, b, a;
			} colors[6];
		};

		const PSCBuf pscb =
		{
			{
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 1.0f, 1.0f, 0.0f, 1.0f },
				{ 1.0f, 0.0f, 0.0f, 1.0f },
				{ 0.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			}
		};

		AddBindable(std::make_unique<PixelConstantBuffer<PSCBuf>>(gfx, pscb));
	}
	void Update(float dt) override
	{
		pitch += dpitch * dt;
		yaw += dyaw * dt;
		roll += droll * dt;
	}
	DirectX::XMMATRIX GetTransformation() const
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	}
private:
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float dpitch = 3.14f;
	float dyaw = 2.1f;
	float droll = 6.28f;
};