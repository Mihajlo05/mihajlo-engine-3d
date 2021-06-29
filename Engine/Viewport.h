#pragma once

#include "Bindable.h"

class Viewport : public Bindable
{
public:
	Viewport(D3D11_VIEWPORT data);
	void Bind(Graphics& gfx) const override;
private:
	D3D11_VIEWPORT data;
};