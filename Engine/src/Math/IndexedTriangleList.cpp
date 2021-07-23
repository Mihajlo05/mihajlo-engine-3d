#include "IndexedTriangleList.h"

namespace dvb = DynamicVertexBuf;

IndexedTriangleList::IndexedTriangleList(IndexBuffer indices, VertexBuffer vertices)
	:
	indices(indices),
	vertices(vertices)
{
	assert(indices.size() % 3 == 0);
}

IndexedTriangleList::IndexedTriangleList(const aiMesh& mesh)
{
	using namespace DirectX;

	dvb::VertexLayout layout;
	layout.Append(dvb::VertexLayout::Position3D);

	bool hasNormals = mesh.HasNormals();

	if (hasNormals)
		layout.Append(dvb::VertexLayout::Normal);

	vertices = VertexBuffer(std::move(layout));

	for (size_t i = 0; i < mesh.mNumVertices; i++)
	{
		const float3 pos = { mesh.mVertices[i].x, mesh.mVertices[i].y , mesh.mVertices[i].z };
		if (hasNormals)
		{
			const float3 normal = { mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z };
			vertices.EmplaceBack(pos, normal);
		}
		else
			vertices.EmplaceBack(pos);
	}

	indices.reserve(mesh.mNumFaces * 3);
	for (size_t i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		assert(face.mNumIndices == 3);

		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
}

IndexedTriangleList::IndexedTriangleList(const std::string& filename, int meshIndex)
{
	using namespace DirectX;
	
	Assimp::Importer imp;
	const aiScene* pModel = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);
	assert(pModel != nullptr);
	
	const aiMesh* pMesh = pModel->mMeshes[meshIndex];

	*this = IndexedTriangleList(*pMesh);
}
