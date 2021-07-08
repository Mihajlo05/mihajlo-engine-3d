#pragma once

#include "IndexedList.h"

template<class Vertex>
class IndexedTriangleList : IndexedList<Vertex>
{
public:
	using IndexedList<Vertex>::Vertices;
	using IndexedList<Vertex>::Indices;
	using IndexedList<Vertex>::GetType;
	using IndexedList<Vertex>::Transform;
public:
	IndexedTriangleList()
		:
		IndexedList<Vertex>(3, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{ }
	IndexedTriangleList& SetNormalsIndependentFlat()
	{
		using namespace DirectX;

		assert(Indices().size() != 0 && Indices().size() % 3 == 0);
		for (size_t i = 0; i < Indices().size(); i += 3)
		{
			auto& v0 = Vertices()[Indices()[i]];
			auto& v1 = Vertices()[Indices()[i + 1]];
			auto& v2 = Vertices()[Indices()[i + 2]];
			const auto p0 = XMLoadFloat3(&v0.pos);
			const auto p1 = XMLoadFloat3(&v1.pos);
			const auto p2 = XMLoadFloat3(&v2.pos);

			const auto n = XMVector3Normalize(XMVector3Cross((p1 - p0), (p2 - p0)));

			XMStoreFloat3(&v0.normal, n);
			XMStoreFloat3(&v1.normal, n);
			XMStoreFloat3(&v2.normal, n);
		}
		return *this;
	}
};