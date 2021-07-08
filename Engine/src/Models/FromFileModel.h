#pragma once

#include <DirectXMath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Math/IndexedTriangleList.h"

class FromFileModel
{
private:
	struct VertexExample
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
	};
public:
	template<class V>
	static IndexedTriangleList<V> MakeWithNormals(const std::string& filename)
	{
		using Itl = IndexedTriangleList<V>;
		using namespace DirectX;

		Assimp::Importer imp;
		const auto pModel = imp.ReadFile(filename,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		const auto pMesh = pModel->mMeshes[0];

		Itl model;

		model.Vertices().reserve(pMesh->mNumVertices);
		for (size_t i = 0; i < pMesh->mNumVertices; i++)
		{
			const XMFLOAT3 pos = { pMesh->mVertices[i].x, pMesh->mVertices[i].y , pMesh->mVertices[i].z };
			const XMFLOAT3 normal = { pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z };
			model.Vertices().push_back({ pos, normal });
		}

		model.Indices().reserve(pMesh->mNumFaces * 3);
		auto& indices = model.Indices();
		for (size_t i = 0; i < pMesh->mNumFaces; i++)
		{
			const auto& face = pMesh->mFaces[i];
			assert(face.mNumIndices == 3);

			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
		return model;
	}
};