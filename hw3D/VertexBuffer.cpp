#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics& gfx) const
{
	const UINT offset = 0u;
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pData.GetAddressOf(), &stride, &offset);
}