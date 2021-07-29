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

	const float4 pscb = { color.x, color.y, color.z, 1.0f };
	auto pcb = std::make_unique<PixelConstantBuffer<float4>>(gfx, pscb);
	pColorCBuf = pcb.get();

	AddBindable(std::move(pcb));

	auto pvs = std::make_unique<VertexShader>(gfx, L"shaders-bin\\DefaultVS.cso");
	VertexShader& vs = *pvs;
	AddBindable(std::move(pvs));

	AddBindable<PixelShader>(gfx, L"shaders-bin\\SolidPS.cso");

	AddBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
	AddBindable<PrimitiveTopology>(model.d3dtype);

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
