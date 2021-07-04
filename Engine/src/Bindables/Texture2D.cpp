#include "Texture2D.h"

using namespace Microsoft::WRL;

Texture2D::Texture2D(Graphics& gfx, const Surface& surf, uint32_t slot)
	:
	slot(slot)
{
	BIND_INFOMAN(gfx);

	ComPtr<ID3D11Texture2D> pTexture;

	D3D11_TEXTURE2D_DESC t2d = {};
	t2d.Width = (UINT)surf.GetWidth();
	t2d.Height = (UINT)surf.GetHeight();
	t2d.MipLevels = 1u;
	t2d.ArraySize = 1u;
	t2d.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	t2d.SampleDesc.Count = 1u;
	t2d.SampleDesc.Quality = 0u;
	t2d.Usage = D3D11_USAGE_DEFAULT;
	t2d.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	t2d.MiscFlags = 0u;
	t2d.CPUAccessFlags = 0u;

	D3D11_SUBRESOURCE_DATA subData;
	subData.pSysMem = surf.GetBufferPointer();
	subData.SysMemPitch = UINT(sizeof(Color) * surf.GetWidth());

	GFX_THROW( GetDevice(gfx)->CreateTexture2D(&t2d, &subData, &pTexture) );

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = t2d.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	GFX_THROW( GetDevice(gfx)->CreateShaderResourceView(pTexture.Get(), &srvDesc, &pData) );
}

void Texture2D::Bind(Graphics& gfx) const
{
	GetContext(gfx)->PSSetShaderResources(slot, 1u, pData.GetAddressOf());
}
