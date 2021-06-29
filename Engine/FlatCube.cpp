#include "FlatCube.h"
#include "CubeModel.h"
#include "DefaultVertex.h"
#include "AllBindables.h"

namespace dx = DirectX;

FlatCube::FlatCube(Graphics& gfx)
	:
	DrawableBase(gfx)
{
	if (!IsStaticInitialized())
	{
		auto indTriangleL = CubeModel::GetWrapped<DefaultVertex>();

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, indTriangleL.Vertices()));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indTriangleL.Indices()));

		struct PixelConstBufData
		{
			struct
			{
				float r, g, b, a;
			} colors[6];
		};

		const PixelConstBufData pixelConstBufData =
		{
			{
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 1.0f, 1.0f, 0.0f, 1.0f },
				{ 1.0f, 0.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f }
			}
		};

		AddStaticBindable(std::make_unique<PixelConstantBuffer<PixelConstBufData>>(gfx, pixelConstBufData));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"FlatPS.cso"));
		auto pvs = std::make_unique<VertexShader>(gfx, L"FlatVS.cso");
		VertexShader& vertexShader = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ieDescs =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u }
		};
		AddStaticBindable(std::make_unique<InputLayout>(gfx, ieDescs, vertexShader.GetBytecode(), vertexShader.GetBytecodeSize()));
	}
	else
	{
		AddIndexBufferFromStatic();
	}

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
}

void FlatCube::Update(float dt)
{
	time += dt;
}

DirectX::XMMATRIX FlatCube::GetTransformation() const
{
	return dx::XMMatrixRotationRollPitchYaw(time, time * 2, time / 2) *
		dx::XMMatrixTranslation(0.0f, 0.0f, 3.0f);
}
