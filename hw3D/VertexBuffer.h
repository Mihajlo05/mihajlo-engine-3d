#pragma once

#include "Graphics.h"
#include <vector>
#include "Bindable.h"
#include <d3d11.h>

class VertexBuffer : public Bindable
{
public:
	template<class Vertex>
	VertexBuffer(Graphics& gfx, const std::vector<Vertex>& vertices)
		:
		stride(sizeof(Vertex))
	{
		BIND_INFOMAN(gfx);

		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = stride * (uint32_t)vertices.size();
		bd.StructureByteStride = stride;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GFX_THROW(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pData));
	}
	void Bind(Graphics& gfx) const override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	const uint32_t stride;
};