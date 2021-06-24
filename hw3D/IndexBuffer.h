#pragma once

#include "Graphics.h"
#include <vector>
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) const override;
	uint32_t GetCount() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	uint32_t count;
};