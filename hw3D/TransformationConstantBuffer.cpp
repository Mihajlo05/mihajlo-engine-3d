#include "TransformationConstantBuffer.h"

TransformationConstantBuffer::TransformationConstantBuffer(Graphics& gfx, const Drawable& parent)
	:
	vConstBuf(gfx),
	parent(parent)
{ }

void TransformationConstantBuffer::Bind(Graphics& gfx) const
{
	vConstBuf.Update(gfx, DirectX::XMMatrixTranspose( parent.GetTransformation() * gfx.GetPerspective() ));
	vConstBuf.Bind(gfx);
}