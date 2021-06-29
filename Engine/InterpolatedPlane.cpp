#include "InterpolatedPlane.h"
#include "PlaneModel.h"
#include "AllBindables.h"
#include "Surface.h"

namespace dx = DirectX;

InterpolatedPlane::InterpolatedPlane(Graphics& gfx)
	:
	DrawableBase(gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			struct { float u, v; } texPos;
		};

		int divs = 100;

		auto indTriangleL = PlaneModel::GetTessellated<Vertex>(divs);

		for (int y = 0; y <= divs; y++)
		{
			for (int x = 0; x <= divs; x++)
			{
				indTriangleL.Vertices()[y * (divs + 1) + x].texPos = { (float)x / divs, 1.0f - (float)y / divs };
			}
		}

		indTriangleL.Transform(dx::XMMatrixScaling(2.0f, 2.0f, 1.0f));
		indTriangleL.Transform(dx::XMMatrixRotationX(7.0f * dx::XM_PI / 18.0f));

		Surface texSurf("Images\\kracc.jpg");
		AddStaticBindable(std::make_unique<Texture2D>(gfx, texSurf));
		AddStaticBindable(std::make_unique<Sampler>(gfx));

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, indTriangleL.Vertices()));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indTriangleL.Indices()));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"Texture2DPS.cso"));
		auto pvs = std::make_unique<VertexShader>(gfx, L"Texture2DVS.cso");
		VertexShader& vertexShader = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ieDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "TEX_POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0u, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0u}
		};
		AddStaticBindable(std::make_unique<InputLayout>(gfx, ieDescs, vertexShader.GetBytecode(), vertexShader.GetBytecodeSize()));
	}
	else
	{
		AddIndexBufferFromStatic();
	}

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this, 0u));

	auto spvcb = std::make_unique<VertexConstantBuffer<WaveBuf>>(gfx, 1u);
	pVCB = spvcb.get();
	AddBindable(std::move(spvcb));
}

void InterpolatedPlane::Update(float dt)
{
	time += dt;

	const WaveBuf wb = { time, 4.0f, 12.0f, 0.1f };
	pVCB->Update(gfx, wb);
}

dx::XMMATRIX InterpolatedPlane::GetTransformation() const
{
	return dx::XMMatrixTranslation(0.0f, 0.0f, 3.0f);
}
