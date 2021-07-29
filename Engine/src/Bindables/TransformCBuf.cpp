#include "TransformCBuf.h"

namespace dx = DirectX;
using namespace Drawables;

namespace Binds
{
	TransformCBuf::TransformCBuf(Graphics& gfx, const Drawable& parent, uint32_t slot)
		:
		parent(parent),
		vConstBuf(gfx, ConstantBuffer<Data>::Type::Vertex, slot)
	{ }

	void TransformCBuf::Bind(Graphics& gfx) const
	{
		vConstBuf.Update(gfx, Data{ dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera().GetView()),
			dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera().GetViewProjection()) });
		vConstBuf.Bind(gfx);
	}
}