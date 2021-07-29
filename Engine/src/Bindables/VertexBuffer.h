#pragma once

#include "Graphics/Graphics.h"
#include <vector>
#include "Bindable.h"
#include <d3d11.h>
#include "Math/Vertex.h"

namespace Binds
{
	class VertexBuffer : public Bindable
	{
	public:
		VertexBuffer(Graphics& gfx, const DynamicVertexBuf::VertexBuffer& vertices)
			:
			stride((uint32_t)vertices.GetLayout().Size())
		{
			BIND_INFOMAN(gfx);

			Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
			D3D11_BUFFER_DESC bd = {};
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0u;
			bd.MiscFlags = 0u;
			bd.ByteWidth = (UINT)vertices.SizeInBytes();
			bd.StructureByteStride = stride;
			D3D11_SUBRESOURCE_DATA sd = {};
			sd.pSysMem = vertices.GetData();
			GFX_THROW(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pData));
		}
		void Bind(Graphics& gfx) const override;
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
		const uint32_t stride;
	};
}