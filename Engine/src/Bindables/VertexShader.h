#pragma once

#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& gfx, const std::wstring& filename);
	void Bind(Graphics& gfx) const override;
	void* GetBytecode() const;
	size_t GetBytecodeSize() const;
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pData;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
};