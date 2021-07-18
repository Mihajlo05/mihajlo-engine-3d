#pragma once

#include "Math/IndexedTriangleList.h"
#include "DrawableBase.h"

class SolidDrawable : public DrawableBase<SolidDrawable>
{
public:
	SolidDrawable(Graphics& gfx, IndexedTriangleList model);
};