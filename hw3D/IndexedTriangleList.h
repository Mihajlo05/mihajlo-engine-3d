#pragma once

#include "IndexedList.h"

template<class Vertex>
class IndexedTriangleList : IndexedList<Vertex>
{
public:
	using IndexedList<Vertex>::Vertices;
	using IndexedList<Vertex>::Indices;
	using IndexedList<Vertex>::GetType;
public:
	IndexedTriangleList()
		:
		IndexedList<Vertex>(3, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{ }
};