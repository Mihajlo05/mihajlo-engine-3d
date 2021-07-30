#pragma once

#include "Math/IndexedTriangleList.h"

namespace Meshes
{
	static IndexedTriangleList cube = IndexedTriangleList("Models\\cube.obj");
	static IndexedTriangleList sphere = IndexedTriangleList("Models\\sphere.obj", true);
}
