#pragma once

#include <vector>
#include <cassert>
#include <d3d11.h>
#include "Index.h"
#include <DirectXMath.h>

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
	void Transform(DirectX::FXMMATRIX matrix)
	{
		for (auto& v : vertices)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
			DirectX::XMStoreFloat3(
				&v.pos,
				DirectX::XMVector3Transform(pos, matrix)
			);
		}
	}
	void SetNormalsIndependentFlat()
	{
		using namespace DirectX;

		assert(indices.size() != 0 && indices.size() % indicesPerPrimitive == 0);
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v0 = vertices[indices[i]];
			auto& v1 = vertices[indices[i + 1]];
			auto& v2 = vertices[indices[i + 2]];
			const auto p0 = XMLoadFloat3(&v0.pos);
			const auto p1 = XMLoadFloat3(&v1.pos);
			const auto p2 = XMLoadFloat3(&v2.pos);

			const auto n = XMVector3Normalize(XMVector3Cross((p1 - p0), (p2 - p0)));

			XMStoreFloat3(&v0.normal, n);
			XMStoreFloat3(&v1.normal, n);
			XMStoreFloat3(&v2.normal, n);
		}
	}
	D3D11_PRIMITIVE_TOPOLOGY GetType()
	{
		return type;
	}
protected:
	IndexedList(uint32_t indicesPerPrimitive, D3D11_PRIMITIVE_TOPOLOGY type)
		:
		type(type),
		indicesPerPrimitive(indicesPerPrimitive)
	{
	}
private:
	VertexList vertices;
	IndexList indices;
	D3D11_PRIMITIVE_TOPOLOGY type;
	uint32_t indicesPerPrimitive;
};