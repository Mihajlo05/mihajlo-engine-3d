#pragma once

#include "Graphics.h"
#include <vector>
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) const override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	const uint32_t stride;
};