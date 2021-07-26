#pragma once

#include "Math/MihajloMath.h"

class ICamera
{
public:
	virtual matrix GetView() const = 0;
	virtual matrix GetProjection() const = 0;
	virtual matrix GetViewProjection() const = 0;
	virtual void SetProjection(fmatrix proj) = 0;
};
