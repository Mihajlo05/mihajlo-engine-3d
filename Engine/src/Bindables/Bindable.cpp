#include "Bindable.h"

using namespace Microsoft::WRL;

namespace Binds
{
	ID3D11Device* Bindable::GetDevice(Graphics& gfx) const
	{
		return gfx.pDevice.Get();
	}

	ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) const
	{
		return gfx.pContext.Get();
	}

#ifndef NDEBUG
	DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) const
	{
		return gfx.infoManager;
	}
#endif
}