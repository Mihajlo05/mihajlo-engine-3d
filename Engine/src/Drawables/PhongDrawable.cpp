#include "PhongDrawable.h"
#include "Bindables/AllBindables.h"

PhongDrawable::PhongDrawable(Graphics& gfx, IndexedTriangleList model, Material material)
	:
	gfx(gfx),
	material(material)
{
	AddBindable<VertexBuffer>(gfx, model.vertices);
	AddIndexBuffer(gfx, model.indices);

	auto pcb = std::make_unique<PixelConstantBuffer<Material>>(gfx, material, cbufSlot);
	pMaterialBuf = pcb.get();
	AddBindable(std::move(pcb));

	if (!IsStaticInitialized())
	{
		
		auto pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddBindable(std::move(pvs));
		AddBindable<PixelShader>(gfx, L"src\\Shaders\\bin\\PhongPS.cso");

		AddBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
		AddBindable<PrimitiveTopology>(model.d3dtype);
	}

	AddBindable<TransformationConstantBuffer>(gfx, *this);
}

void PhongDrawable::SetMaterial(Material m)
{
	assert(pMaterialBuf != nullptr);
	material = m;
	pMaterialBuf->Update(gfx, material);
}

PhongDrawable::Material PhongDrawable::GetMaterial() const
{
	return material;
}
