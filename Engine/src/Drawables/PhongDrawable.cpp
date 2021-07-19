#include "PhongDrawable.h"
#include "Bindables/AllBindables.h"

PhongDrawable::PhongDrawable(Graphics& gfx, IndexedTriangleList model, Material material)
{
	AddBindable<VertexBuffer>(gfx, model.vertices);
	AddIndexBuffer(gfx, model.indices);

	if (!IsStaticInitialized())
	{
		AddStaticBindable<PixelConstantBuffer<Material>>(gfx, material, cbufSlot);
		
		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddBindable(std::move(pvs));
		AddBindable<PixelShader>(gfx, L"src\\Shaders\\bin\\PhongPS.cso");

		AddBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
		AddBindable<PrimitiveTopology>(model.d3dtype);
	}

	AddBindable<TransformationConstantBuffer>(gfx, *this);
}