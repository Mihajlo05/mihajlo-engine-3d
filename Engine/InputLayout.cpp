#include "InputLayout.h"

InputLayout::InputLayout(Graphics& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescriptors, void* bytecode, size_t bytecodeLength)
{
	BIND_INFOMAN(gfx);

	GFX_THROW(GetDevice(gfx)->CreateInputLayout(
		elementDescriptors.data(), (UINT)elementDescriptors.size(),
		bytecode,
		bytecodeLength,
		&pData
	));
}

void InputLayout::Bind(Graphics& gfx) const
{
	GetContext(gfx)->IASetInputLayout(pData.Get());
}
