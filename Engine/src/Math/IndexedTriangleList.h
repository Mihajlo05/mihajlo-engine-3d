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
	IndexedTriangleList(const std::string& filename); //loads first mesh from file
	static constexpr D3D11_PRIMITIVE_TOPOLOGY GetD3D11Type();
public:
	IndexBuffer indices;
	VertexBuffer vertices;
};
