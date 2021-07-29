#include "Solid.h"
#include "Bindables/AllBindables.h"

using namespace Binds;
ConstantBuffer<float4>* Drawables::Solid::pColorCBuf = nullptr;

namespace Drawables
{
	Solid::Solid(Graphics& gfx, IndexedTriangleList model, float3 color)
		:
		gfx(gfx),
		color(color)
	{
		AddBind(std::make_shared<VertexBuffer>(gfx, model.vertices));
		AddBind(std::make_shared<IndexBuffer>(gfx, model.indices));

		const float4 pscb = { color.x, color.y, color.z, 1.0f };
		auto pcb = std::make_shared<ConstantBuffer<float4>>(gfx, ConstantBuffer<float4>::Type::Pixel, pscb);
		pColorCBuf = pcb.get();

		AddBind(std::move(pcb));

		auto pvs = std::make_shared<VertexShader>(gfx, "shaders-bin\\DefaultVS.cso");
		VertexShader& vs = *pvs;
		AddBind(std::move(pvs));

		AddBind(std::make_shared<PixelShader>(gfx, "shaders-bin\\SolidPS.cso"));

		AddBind(std::make_shared<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize()));
		AddBind(std::make_shared<PrimitiveTopology>(model.d3dtype));

		AddBind(std::make_shared<TransformationConstantBuffer>(gfx, *this));
	}

	void Solid::SetColor(float3 c)
	{
		assert(pColorCBuf != nullptr);
		color = c;
		pColorCBuf->Update(gfx, { c.x, c.y, c.z, 1.0f });
	}

	float3 Solid::GetColor() const
	{
		return color;
	}
}
