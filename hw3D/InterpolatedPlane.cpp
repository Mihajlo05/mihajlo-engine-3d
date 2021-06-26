#include "InterpolatedPlane.h"
#include "PlaneModel.h"
#include "AllBindables.h"

namespace dx = DirectX;

InterpolatedPlane::InterpolatedPlane(Graphics& gfx)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
			struct { float r, g, b; } color;
		};

		auto indTriangleL = PlaneModel::GetTessellated<Vertex>();

		indTriangleL.Vertices()[0].color = { 1.0f, 1.0f, 1.0f };
		indTriangleL.Vertices()[1].color = { 1.0f, 1.0f, 0.0f };
		indTriangleL.Vertices()[2].color = { 1.0f, 0.0f, 1.0f };
		indTriangleL.Vertices()[3].color = { 0.0f, 1.0f, 1.0f };

		indTriangleL.Transform(dx::XMMatrixRotationX(4 * dx::XM_PI / 9));

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

void InterpolatedPlane::UpdateLogic(float dt)
{
	time += dt;
}

void InterpolatedPlane::UpdateGraphics(Graphics& gfx)
{
}

dx::XMMATRIX InterpolatedPlane::GetTransformation() const
{
	return dx::XMMatrixTranslation(0.0f, 0.0f, 3.0f);
}
