#include "InputLayout.h"

namespace Binds
{
	InputLayout::InputLayout(Graphics& gfx, const DynamicVertexBuf::VertexLayout& layout, void* bytecode, size_t bytecodeLength)
	{
		BIND_INFOMAN(gfx);

		GFX_THROW(GetDevice(gfx)->CreateInputLayout(
			layout.GetD3DLayout().data(), (UINT)layout.GetElementCount(),
			bytecode,
			bytecodeLength,
			&pData
		));
	}

	void InputLayout::Bind(Graphics& gfx) const
	{
		GetContext(gfx)->IASetInputLayout(pData.Get());
	}
}