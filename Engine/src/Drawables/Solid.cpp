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
		static int tagIndex = 0;
		tagIndex++;
		std::string tag = "SolidTag" + std::to_string(tagIndex);

		AddBind(VertexBuffer::Resolve(gfx, tag, model.vertices));
		AddBind(IndexBuffer::Resolve(gfx, tag, model.indices));

		const float4 pscb = { color.x, color.y, color.z, 1.0f };
		auto pcb = ConstantBuffer<float4>::Resolve(gfx, ConstantBuffer<float4>::Type::Pixel, pscb);
		pColorCBuf = pcb.get();

		AddBind(std::move(pcb));

		auto pvs = VertexShader::Resolve(gfx, "shaders-bin\\DefaultVS.cso");
		VertexShader& vs = *pvs;
		AddBind(std::move(pvs));

		AddBind(PixelShader::Resolve(gfx, "shaders-bin\\SolidPS.cso"));

		AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), vs.GetBytecode(), vs.GetBytecodeSize()));
		AddBind(PrimitiveTopology::Resolve(gfx, model.d3dtype));

		AddBind(std::make_shared<TransformCBuf>(gfx, *this));
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
