#include "PhongDrawable.h"
#include "Bindables/AllBindables.h"

PhongDrawable::PhongDrawable(Graphics& gfx, IndexedTriangleList<Vertex> model, const MaterialData& mData)
	:
	DrawableBase(gfx),
	mData(mData)
{
	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.Indices()));
	AddBindable(std::make_unique<VertexBuffer>(gfx, model.Vertices()));
	AddBindable(std::make_unique<PrimitiveTopology>(model.GetType()));

	if (!IsStaticInitialized())
	{

		AddStaticBindable(std::make_unique<PixelShader>(gfx, L"src\\Shaders\\bin\\PhongPS.cso"));
		std::unique_ptr<VertexShader> pvs = std::make_unique<VertexShader>(gfx, L"src\\Shaders\\bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddStaticBindable(std::move(pvs));

		std::vector<D3D11_INPUT_ELEMENT_DESC> ieds;
		ieds.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u });
		ieds.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0u, sizeof(DirectX::XMFLOAT3), D3D11_INPUT_PER_VERTEX_DATA, 0u });

		AddStaticBindable(std::make_unique<InputLayout>(gfx, ieds, vs.GetBytecode(), vs.GetBytecodeSize()));
	}

	AddBindable(std::make_unique<TransformationConstantBuffer>(gfx, *this));
	
	auto pPCB = std::make_unique<PixelConstantBuffer<MaterialData>>(gfx, mData, 1u);
	pPixelConstantBuffer = pPCB.get();
	AddBindable(std::move(pPCB));
}

PhongDrawable::MaterialData PhongDrawable::GetMaterialData() const
{
	return mData;
}

void PhongDrawable::SetMaterialData(const PhongDrawable::MaterialData& mData)
{
	this->mData = mData;
	pPixelConstantBuffer->SetData(mData);
}
