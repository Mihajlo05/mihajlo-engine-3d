#include "TransformationConstantBuffer.h"

namespace dx = DirectX;
using VConstBuf = VertexConstantBuffer<dx::XMMATRIX>;

TransformationConstantBuffer::TransformationConstantBuffer(Graphics& gfx, const Drawable& parent, uint32_t slot)
	:
	parent(parent),
	vConstBuf(gfx, slot)
{ }

void TransformationConstantBuffer::Bind(Graphics& gfx) const
{
	vConstBuf.Update(gfx, Data{ dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera()),
		dx::XMMatrixTranspose(parent.GetTransformation() * gfx.GetCamera() * gfx.GetPerspective()) });
	vConstBuf.Bind(gfx);
}