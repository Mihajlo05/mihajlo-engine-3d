#include "Viewport.h"

namespace Binds
{
	Viewport::Viewport(D3D11_VIEWPORT data)
		:
		data(data)
	{ }

	void Viewport::Bind(Graphics& gfx) const
	{
		GetContext(gfx)->RSSetViewports(1u, &data);
	}
}