#include "Phong.h"
#include "Bindables/AllBindables.h"

using namespace Binds;

namespace Drawables
{
	Phong::Phong(Graphics& gfx, IndexedTriangleList model, Material material)
		:
		gfx(gfx),
		material(material)
	{
		static int tagIndex = 0;
		tagIndex++;
		std::string tag = "PhongTag" + std::to_string(tagIndex);

		AddBind(VertexBuffer::Resolve(gfx, tag, model.vertices));
		AddBind(IndexBuffer::Resolve(gfx, tag, model.indices));

		auto pcb = ConstantBuffer<Material>::Resolve(gfx, ConstantBuffer<Material>::Type::Pixel, material, cbufSlot);
		pMaterialBuf = pcb.get();
		AddBind(std::move(pcb));

		auto pvs = VertexShader::Resolve(gfx, "shaders-bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddBind(std::move(pvs));
		AddBind(PixelShader::Resolve(gfx, "shaders-bin\\PhongPS.cso"));

		AddBind(InputLayout::Resolve(gfx, model.vertices.GetLayout(), vs.GetBytecode(), vs.GetBytecodeSize()));
		AddBind(PrimitiveTopology::Resolve(gfx, model.d3dtype));

		AddBind(std::make_shared<TransformCBuf>(gfx, *this));
	}

	void Phong::Draw(Graphics& gfx) const
	{
		if (pLight != nullptr)
		{
			pLight->Bind(gfx);
		}
		Drawable::Draw(gfx);
	}

	void Phong::SetLight(const PointLight& pcb)
	{
		pLight = &pcb;
	}

	void Phong::SetMaterial(Material m)
	{
		assert(pMaterialBuf != nullptr);
		material = m;
		pMaterialBuf->Update(gfx, material);
	}

	Phong::Material Phong::GetMaterial() const
	{
		return material;
	}
}
