#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, std::vector<Index>& indices)
	:
	count((uint32_t)indices.size())
{
	BIND_INFOMAN(gfx);

	UINT stride = sizeof(Index);

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = static_cast<UINT>(stride * indices.size());
	ibd.StructureByteStride = stride;
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	GFX_THROW(GetDevice(gfx)->CreateBuffer(&ibd, &isd, &pData));
}

void IndexBuffer::Bind(Graphics& gfx) const
{
	GetContext(gfx)->IASetIndexBuffer(pData.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

uint32_t IndexBuffer::GetCount() const
{
	return count;
}