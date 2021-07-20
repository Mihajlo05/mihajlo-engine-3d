#include "SolidDrawable.h"
#include "Bindables/AllBindables.h"

PixelConstantBuffer<float4>* SolidDrawable::pColorCBuf = nullptr;

SolidDrawable::SolidDrawable(Graphics& gfx, IndexedTriangleList model, float3 color)
	:
	gfx(gfx),
	color(color)
{
	AddBindable<VertexBuffer>(gfx, model.vertices);
	AddIndexBuffer(gfx, model.indices);
	if (!IsStaticInitialized())
	{
		const float4 pscb = { color.x, color.y, color.z, 1.0f };
		auto pcb = std::make_unique<PixelConstantBuffer<float4>>(gfx, pscb);
		pColorCBuf = pcb.get();

		AddStaticBindable(std::move(pcb));

		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\DefaultVS.cso");
		VertexShader& vs = *pvs;
		AddStaticBindable(std::move(pvs));

		AddStaticBindable<PixelShader>(gfx, L"src\\Shaders\\bin\\SolidPS.cso");

		AddStaticBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
		AddStaticBindable<PrimitiveTopology>(model.d3dtype);
	}

	AddBindable<TransformationConstantBuffer>(gfx, *this);
}

void SolidDrawable::SetColor(float3 c)
{
	assert(pColorCBuf != nullptr);
	color = c;
	pColorCBuf->Update(gfx, {c.x, c.y, c.z, 1.0f});
}

float3 SolidDrawable::GetColor() const
{
	return color;
}
