#include "SolidDrawable.h"
#include "Bindables/AllBindables.h"

SolidDrawable::SolidDrawable(Graphics& gfx, IndexedTriangleList model)
{
	AddBindable<VertexBuffer>(gfx, model.vertices);
	AddIndexBuffer(gfx, model.indices);
	if (!IsStaticInitialized())
	{
		struct PSCBuf
		{
			float r, g, b, a;
		};

		const PSCBuf pscb = { 1.0f, 1.0f, 1.0f, 1.0f };
		AddStaticBindable<PixelConstantBuffer<PSCBuf>>(gfx, pscb);

		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\DefaultVS.cso");
		VertexShader& vs = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable<PixelShader>(gfx, L"src\\Shaders\\bin\\SolidPS.cso");

		AddStaticBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
		AddStaticBindable<PrimitiveTopology>(model.d3dtype);
	}

	AddBindable<TransformationConstantBuffer>(gfx, *this);
}