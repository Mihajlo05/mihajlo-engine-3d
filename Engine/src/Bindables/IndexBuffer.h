#pragma once

#include "Graphics/Graphics.h"
#include <vector>
#include "Bindable.h"
#include "Math/Index.h"

namespace Binds
{
	class IndexBuffer : public Bindable
	{
	public:
		IndexBuffer(Graphics& gfx, const std::string& tag, const std::vector<Index>& indices);
		void Bind(Graphics& gfx) const override;
		uint32_t GetCount() const;
		static std::shared_ptr<IndexBuffer> Resolve(Graphics& gfx, const std::string& tag, const std::vector<Index>& indices)
		{
			return Codex::Resolve<IndexBuffer>(gfx, tag, indices);
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
			return typeid(IndexBuffer).name() + "#"s + tag;
		}
	private:
		std::string tag;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
		uint32_t count;
	};
}