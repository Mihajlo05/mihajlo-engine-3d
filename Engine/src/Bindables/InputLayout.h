#pragma once

#include "Bindable.h"
#include "Math/Vertex.h"

namespace Binds
{
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx, const DynamicVertexBuf::VertexLayout& layout, void* bytecode, size_t bytecodeLength);
		void Bind(Graphics& gfx) const override;
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pData;
	};
}