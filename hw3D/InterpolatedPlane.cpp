#include "InterpolatedPlane.h"
#include "PlaneModel.h"
#include "AllBindables.h"
#include <random>

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
			struct { float r, g, b; } color;
		};

		auto indTriangleL = PlaneModel::GetTessellated<Vertex>(100 );

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float> cDist(0.0f, 1.0f);

		for (auto& v : indTriangleL.Vertices())
		{
			v.color = { cDist(rng), cDist(rng), cDist(rng) };
		}

		indTriangleL.Transform(dx::XMMatrixScaling(2.0f, 2.0f, 1.0f));
		indTriangleL.Transform(dx::XMMatrixRotationX(7.0f * dx::XM_PI / 18.0f));

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, indTriangleL.Vertices()));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indTriangleL.Indices()));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"InterpolatedPS.cso"));
		auto pvs = std::make_unique<VertexShader>(gfx, L"InterpolatedPlaneVS.cso");
		VertexShader& vertexShader = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ieDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0u}
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
