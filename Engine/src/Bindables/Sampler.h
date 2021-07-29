#pragma once

#include "Bindable.h"

namespace Binds
{
	class Sampler : public Bindable
	{
	public:
		Sampler(Graphics& gfx, uint32_t slot = 0u);
		void Bind(Graphics& gfx) const override;
		static std::shared_ptr<Sampler> Resolve(Graphics& gfx, uint32_t slot = 0)
		{
			return Codex::Resolve<Sampler>(gfx, slot);
		}
		static std::string GenerateUID(uint32_t slot)
		{
			using namespace std::string_literals;
			return typeid(Sampler).name() + "#"s + std::to_string(slot);
		}
		std::string GetUID() const override
		{
			return GenerateUID(slot);
		}
	private:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pData;
		uint32_t slot;
	};
}