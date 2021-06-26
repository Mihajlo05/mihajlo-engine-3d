#include "InterpolatedCube.h"
#include "CubeModel.h"
#include "AllBindables.h"

namespace dx = DirectX;

InterpolatedCube::InterpolatedCube(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			struct { float x, y, z; } pos;
			struct { float r, g, b; } color;
		};
		
		auto indTriangleL = CubeModel::GetWrapped<Vertex>();

		indTriangleL.Vertices()[0].color = { 1.0f, 1.0f, 1.0f };
		indTriangleL.Vertices()[1].color = { 1.0f, 1.0f, 0.0f };
		indTriangleL.Vertices()[2].color = { 1.0f, 0.0f, 1.0f };
		indTriangleL.Vertices()[3].color = { 0.0f, 1.0f, 1.0f };
		indTriangleL.Vertices()[4].color = { 0.0f, 0.0f, 1.0f };
		indTriangleL.Vertices()[5].color = { 0.0f, 1.0f, 0.0f };
		indTriangleL.Vertices()[6].color = { 1.0f, 0.0f, 0.0f };
		indTriangleL.Vertices()[7].color = { 0.0f, 0.0f, 0.0f };

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, indTriangleL.Vertices()));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indTriangleL.Indices()));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"InterpolatedPS.cso"));
		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorPosVS.cso");
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

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
}

void InterpolatedCube::UpdateLogic(float dt)
{
	time += dt;
}

void InterpolatedCube::UpdateGraphics(Graphics& gfx)
{
}

DirectX::XMMATRIX InterpolatedCube::GetTransformation() const
{
	return dx::XMMatrixRotationRollPitchYaw(time, time/2.0f, time*2.0f) *
		dx::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
}
