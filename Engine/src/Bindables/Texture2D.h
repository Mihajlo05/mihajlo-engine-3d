#pragma once

#include "Bindable.h"
#include "Graphics/Surface.h"

namespace Binds
{
	class Texture2D : public Bindable
	{
	public:
		Texture2D(Graphics& gfx, const std::string& path, uint32_t slot = 0u);
		void Bind(Graphics& gfx) const override;
		static std::shared_ptr<Texture2D> Resolve(Graphics& gfx, const std::string& path, uint32_t slot = 0u)
		{
			return Codex::Resolve<Texture2D>(gfx, path, slot);
		}
		static std::string GenerateUID(const std::string& path, uint32_t slot)
		{
			using namespace std::string_literals;
			return typeid(Texture2D).name() + "#"s + path + "#"s + std::to_string(slot);
		}
		std::string GetUID() const override
		{
			return GenerateUID(path, slot);
		}
	private:
		std::string path;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pData;
		uint32_t slot;
	};
}