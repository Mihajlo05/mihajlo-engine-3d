#include "TransformationConstantBuffer.h"

namespace dx = DirectX;
using namespace Drawables;

TransformationConstantBuffer::TransformationConstantBuffer(Graphics& gfx, const Drawable& parent, uint32_t slot)
	:
	parent(parent),
	vConstBuf(gfx, ConstantBuffer<Data>::Type::Vertex, slot)
{ }

void TransformationConstantBuffer::Bind(Graphics& gfx) const
{
	vConstBuf.Update(gfx, Data{ dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera().GetView()),
		dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera().GetViewProjection()) });
	vConstBuf.Bind(gfx);
}