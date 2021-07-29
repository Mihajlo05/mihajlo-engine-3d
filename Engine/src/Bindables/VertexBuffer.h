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
		VertexBuffer(Graphics& gfx, const std::string& tag, const DynamicVertexBuf::VertexBuffer& vertices)
			:
			stride((uint32_t)vertices.GetLayout().Size()),
			tag(tag)
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
		static std::shared_ptr<VertexBuffer> Resolve(Graphics& gfx, const std::string& tag, const DynamicVertexBuf::VertexBuffer& vertices)
		{
			return Codex::Resolve<VertexBuffer>(gfx, tag, vertices);
		}
		template<typename... Ignore>
		static std::string GenerateUID(const std::string& tag, Ignore&&... ignore)
		{
			return _GenerateUID(tag);
		}
		std::string GetUID() const override
		{
			return GenerateUID(tag);
		}
	private:
		static std::string _GenerateUID(const std::string& tag)
		{
			using namespace std::string_literals;
			return typeid(VertexBuffer).name() + "#"s + tag;
		}
	private:
		std::string tag;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
		const uint32_t stride;
	};
}