#pragma once

#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& gfx, const std::wstring& filename);
	void Bind(Graphics& gfx) const override;
	void* GetBytecode() const;
	size_t GetBytecodeLength() const;
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pData;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
};