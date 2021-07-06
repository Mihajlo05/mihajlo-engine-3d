#include "SolidSphere.h"
#include "Bindables/AllBindables.h"
#include "Models/SphereModel.h"
#include "Math/IndexedTriangleList.h"
#include "Math/DefaultVertex.h"
#include "Bindables/AllBindables.h"

SolidSphere::SolidSphere(Graphics& gfx, Color c)
	:
	DrawableBase(gfx)
{
	if (!IsStaticInitialized())
	{
		IndexedTriangleList<DefaultVertex> itl = SphereModel::Make<DefaultVertex>();

		const float scale = 1.0f / 3.0f;
		itl.Transform(DirectX::XMMatrixScaling(scale, scale, scale));

		AddStaticBindable(std::make_unique<VertexBuffer>(gfx, itl.Vertices()));
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, itl.Indices()));
		AddStaticBindable(std::make_unique<PrimitiveTopology>(itl.GetType()));

		struct PCBData
		{
			DirectX::XMFLOAT4 color;
		};

		const float cf = 1.0f / 255.0f;
		const PCBData pcbd = { { (float)c.GetR() * cf,
								 (float)c.GetG() * cf,
								 (float)c.GetB() * cf,
								 1.0f } };

		AddStaticBindable(std::make_unique<PixelConstantBuffer<PCBData>>(gfx, pcbd));

		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\DefaultVS.cso");
		VertexShader& vs = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"src\\Shaders\\bin\\SolidPS.cso"));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ieds;
		ieds.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u });

		AddStaticBindable(std::make_unique<InputLayout>(gfx, ieds, vs.GetBytecode(), vs.GetBytecodeSize()));
	}
	else
	{
		AddIndexBufferFromStatic();
	}

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
}