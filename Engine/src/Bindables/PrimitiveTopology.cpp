#include "PrimitiveTopology.h"

namespace Binds
{
	PrimitiveTopology::PrimitiveTopology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
		:
		data(type)
	{ }

	void PrimitiveTopology::Bind(Graphics& gfx) const
	{
		GetContext(gfx)->IASetPrimitiveTopology(data);
	}
}