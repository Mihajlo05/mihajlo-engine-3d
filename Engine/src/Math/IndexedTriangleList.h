#pragma once

#include "Graphics/Graphics.h"
#include "Vertex.h"
#include "Index.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class IndexedTriangleList
{
public:
	using IndexBuffer = std::vector<Index>;
	using VertexBuffer = DynamicVertexBuf::VertexBuffer;
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(IndexBuffer indices, VertexBuffer vertices);
	IndexedTriangleList(const aiMesh& mesh); //creates Itl from aiMesh
	IndexedTriangleList(const std::string& filename, int meshIndex = 0); //loads mesh from file
public:
	IndexBuffer indices;
	VertexBuffer vertices;
	static constexpr D3D11_PRIMITIVE_TOPOLOGY d3dtype = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};
