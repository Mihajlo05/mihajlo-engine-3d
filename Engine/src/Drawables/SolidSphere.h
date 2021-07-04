#pragma once

#include "DrawableBase.h"
#include "Graphics/Color.h"

class SolidSphere : public DrawableBase<SolidSphere>
{
public:
	SolidSphere(Graphics& gfx, Color c);
};