#pragma once

#include <vector>
#include <cassert>
#include <d3d11.h>
#include "Index.h"

template<class Vertex>
class IndexedList
{
public:
	using VertexList = std::vector<Vertex>;
	using IndexList = std::vector<Index>;
public:
	VertexList& Vertices()
	{
		return vertices;
	}
	IndexList& Indices()
	{
		return indices;
	}
	D3D11_PRIMITIVE_TOPOLOGY GetType()
	{
		return type;
	}
protected:
	IndexedList(uint32_t indicesPerPrimitive, D3D11_PRIMITIVE_TOPOLOGY type)
		:
		type(type)
	{
		assert(indices.size() % indicesPerPrimitive == 0);
	}
private:
	VertexList vertices;
	IndexList indices;
	D3D11_PRIMITIVE_TOPOLOGY type;
};