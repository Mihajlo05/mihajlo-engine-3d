#pragma once

#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescriptors, void* bytecode, size_t bytecodeLength);
	void Bind(Graphics& gfx) const override;
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pData;
};