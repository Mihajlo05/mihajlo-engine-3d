#include "VertexShader.h"
#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

VertexShader::VertexShader(Graphics& gfx, const std::wstring& filename)
{
	BIND_INFOMAN(gfx);

	GFX_THROW(D3DReadFileToBlob(filename.c_str(), &pBlob));
	GFX_THROW(GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pData));

}

void VertexShader::Bind(Graphics& gfx) const
{
	GetContext(gfx)->VSSetShader(pData.Get(), nullptr, 0u);
}

void* VertexShader::GetBytecode() const
{
	return pBlob->GetBufferPointer();
}

size_t VertexShader::GetBytecodeSize() const
{
	return pBlob->GetBufferSize();
}
