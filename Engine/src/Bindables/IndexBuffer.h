#pragma once

#include "Graphics/Graphics.h"
#include <vector>
#include "Bindable.h"
#include "Math/Index.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graphics& gfx, std::vector<Index>& indices);
	void Bind(Graphics& gfx) const override;
	uint32_t GetCount() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	uint32_t count;
};