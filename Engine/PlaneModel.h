#pragma once

#include "IndexedTriangleList.h"
#include "DefaultVertex.h"

class PlaneModel
{
public:
	template<class Vertex>
	static IndexedTriangleList<Vertex> GetTessellated(int divisions = 1)
	{
		IndexedTriangleList<Vertex> itl;

		float step = 2.0f / static_cast<float>(divisions);

		for (int y = 0; y <= divisions; y++)
		{
			float yCoord = y * step - 1.0f;
			for (int x = 0; x <= divisions; x++)
			{
				itl.Vertices().push_back({ {x * step - 1.0f, yCoord, 0.0f} });
			}
		}

		for (int y = 0; y < divisions; y++)
		{
			for (int x = 0; x < divisions; x++)
			{
				itl.Indices().push_back(y * (divisions + 1) + x);
				itl.Indices().push_back((y + 1) * (divisions + 1) + x);
				itl.Indices().push_back(y * (divisions + 1) + x + 1);
				itl.Indices().push_back(y * (divisions + 1) + x + 1);
				itl.Indices().push_back((y + 1) * (divisions + 1) + x);
				itl.Indices().push_back((y + 1) * (divisions + 1) + x + 1);
			}
		}

		return itl;
	}
};