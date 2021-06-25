#include "TransformationConstantBuffer.h"

namespace dx = DirectX;
using VConstBuf = VertexConstantBuffer<dx::XMMATRIX>;

std::unique_ptr<VConstBuf> TransformationConstantBuffer::pVConstBuf;

TransformationConstantBuffer::TransformationConstantBuffer(Graphics& gfx, const Drawable& parent)
	:
	parent(parent)
{
	if (pVConstBuf.get() == nullptr)
	{
		pVConstBuf = std::make_unique<VConstBuf>(gfx);
	}
}

void TransformationConstantBuffer::Bind(Graphics& gfx) const
{
	pVConstBuf->Update(gfx, dx::XMMatrixTranspose( parent.GetTransformation() * gfx.GetPerspective() ));
	pVConstBuf->Bind(gfx);
}