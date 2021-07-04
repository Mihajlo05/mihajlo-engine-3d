#include "FlatCube.h"
#include "Models/CubeModel.h"
#include "Math/DefaultVertex.h"
#include "Bindables/AllBindables.h"
#include <memory>

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

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"src\\Shaders\\bin\\FlatPS.cso"));
		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\DefaultVS.cso");
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