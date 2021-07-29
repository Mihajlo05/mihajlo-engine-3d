#pragma once

#include "Bindable.h"

namespace Binds
{
	class PrimitiveTopology : public Bindable
	{
	public:
		PrimitiveTopology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
		void Bind(Graphics& gfx) const override;
		static std::shared_ptr<PrimitiveTopology> Resolve(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
		{
			return Codex::Resolve<PrimitiveTopology>(gfx, type);
		}
		static std::string GenerateUID(D3D11_PRIMITIVE_TOPOLOGY type)
		{
			using namespace std::string_literals;
			return typeid(PrimitiveTopology).name() + "#"s + std::to_string(type);
		}
		std::string GetUID() const override
		{
			return GenerateUID(data);
		}
	private:
		D3D11_PRIMITIVE_TOPOLOGY data;
	};
}