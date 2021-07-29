#pragma once

#include "Bindable.h"
#include "Math/Vertex.h"

namespace Binds
{
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx, const DynamicVertexBuf::VertexLayout& layout, void* bytecode, size_t bytecodeLength);
		void Bind(Graphics& gfx) const override;
		static std::shared_ptr<InputLayout> Resolve(Graphics& gfx,
			const DynamicVertexBuf::VertexLayout& layout, void* bytecode, size_t bytecodeLength)
		{
			return Codex::Resolve<InputLayout>(gfx, layout, bytecode, bytecodeLength);
		}
		template<typename... Ignore>
		static std::string GenerateUID(const DynamicVertexBuf::VertexLayout& layout, Ignore&&... ignore)
		{
			return _GenerateUID(layout);
		}
		std::string GetUID() const override
		{
			return GenerateUID(layout);
		}
	private:
		static std::string _GenerateUID(const DynamicVertexBuf::VertexLayout& layout)
		{
			using namespace std::string_literals;
			return typeid(InputLayout).name() + "#"s + layout.GetCode();
		}
	private:
		DynamicVertexBuf::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pData;
	};
}