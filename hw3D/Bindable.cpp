#include "Bindable.h"

using namespace Microsoft::WRL;

ComPtr<ID3D11Device> Bindable::GetDevice(Graphics& gfx) const
{
	return gfx.pDevice;
}

ComPtr<ID3D11DeviceContext> Bindable::GetContext(Graphics& gfx) const
{
	return gfx.pContext;
}

#ifndef NDEBUG
DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) const
{
	return gfx.infoManager;
}
#endif