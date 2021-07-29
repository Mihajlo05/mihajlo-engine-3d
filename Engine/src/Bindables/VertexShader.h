#pragma once

#include "Bindable.h"

namespace Binds
{
	class VertexShader : public Bindable
	{
	public:
		VertexShader(Graphics& gfx, const std::string& filename);
		void Bind(Graphics& gfx) const override;
		void* GetBytecode() const;
		size_t GetBytecodeSize() const;
		static std::shared_ptr<VertexShader> Resolve(Graphics& gfx, const std::string& filename)
		{
			return Codex::Resolve<VertexShader>(gfx, filename);
		}
		static std::string GenerateUID(const std::string& filename)
		{
			using namespace std::string_literals;
			return typeid(VertexShader).name() + "#"s + filename;
		}
		std::string GetUID() const override
		{
			return GenerateUID(filename);
		}
	private:
		std::string filename;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pData;
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	};
}