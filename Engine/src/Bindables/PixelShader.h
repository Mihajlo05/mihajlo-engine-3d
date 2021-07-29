#pragma once

#include "Bindable.h"

namespace Binds
{
	class PixelShader : public Bindable
	{
	public:
		PixelShader(Graphics& gfx, const std::string& filename);
		void Bind(Graphics& gfx) const override;
		void* GetBytecode() const;
		size_t GetBytecodeLength() const;
		static std::shared_ptr<PixelShader> Resolve(Graphics& gfx, const std::string& filename)
		{
			return Codex::Resolve<PixelShader>(gfx, filename);
		}
		static std::string GenerateUID(const std::string& filename)
		{
			using namespace std::string_literals;
			return typeid(PixelShader).name() + "#"s + filename;
		}
		std::string GetUID() const override
		{
			return GenerateUID(filename);
		}
	private:
		std::string filename;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pData;
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	};
}