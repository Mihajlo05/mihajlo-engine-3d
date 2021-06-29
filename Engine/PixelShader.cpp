#include "PixelShader.h"
#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

PixelShader::PixelShader(Graphics& gfx, const std::wstring& filename)
{
	BIND_INFOMAN(gfx);

	GFX_THROW(D3DReadFileToBlob(filename.c_str(), &pBlob));
	GFX_THROW(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pData));
}

void PixelShader::Bind(Graphics& gfx) const
{
	GetContext(gfx)->PSSetShader(pData.Get(), nullptr, 0u);
}

void* PixelShader::GetBytecode() const
{
	return pBlob->GetBufferPointer();
}

size_t PixelShader::GetBytecodeLength() const
{
	return pBlob->GetBufferSize();
}
