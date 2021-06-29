#pragma once

#include "Bindable.h"

class PrimitiveTopology : public Bindable
{
public:
	PrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Graphics& gfx) const override;
private:
	D3D11_PRIMITIVE_TOPOLOGY data;
};