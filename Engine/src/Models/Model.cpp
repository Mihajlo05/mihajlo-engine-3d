#include "Model.h"
#include "assimp.h"
#include "Math/IndexedTriangleList.h"
#include "Drawables/Drawable.h"
#include "Drawables/PhongDrawable.h"
#include "Nodes/MeshInstance.h"

std::shared_ptr<PhongDrawable> ParseMesh(Graphics& gfx, const aiMesh& amesh, const aiMaterial* const* pMaterials);
std::unique_ptr<Node> ParseNode(const aiNode& anode, const std::vector<std::shared_ptr<PhongDrawable>>& meshPtrs, aiMesh** const aiMeshes);

std::unique_ptr<Node> LoadModel(Graphics& gfx, const std::string& filename, const PointLight* pLight)
{
	Assimp::Importer imp;
	const aiScene* pModel = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

	std::vector<std::shared_ptr<PhongDrawable>> meshPtrs;
	meshPtrs.reserve(pModel->mNumMeshes);
	for (unsigned int i = 0; i < pModel->mNumMeshes; i++)
	{
		meshPtrs.push_back(ParseMesh(gfx, *pModel->mMeshes[i], pModel->mMaterials));
		if (pLight) meshPtrs[i]->SetLight(*pLight);
	}

	return ParseNode(*pModel->mRootNode, meshPtrs, pModel->mMeshes);
}

std::shared_ptr<PhongDrawable> ParseMesh(Graphics& gfx, const aiMesh& amesh, const aiMaterial* const* pMaterials)
{
	const aiMaterial& material = *pMaterials[amesh.mMaterialIndex];

	IndexedTriangleList itl(amesh);
	return std::make_shared<PhongDrawable>(gfx, itl, PhongDrawable::Material{ {1, 1, 1}, 4, 100 });
}

std::unique_ptr<Node> ParseNode(const aiNode& anode, const std::vector<std::shared_ptr<PhongDrawable>>& meshPtrs, aiMesh** const aiMeshes)
{
	aiVector3D pos;
	aiVector3D rot;
	aiVector3D scaling;
	anode.mTransformation.Decompose(scaling, rot, pos);

	std::unique_ptr<Node> pNode;

	switch (anode.mNumMeshes)
	{
	case 0:
		pNode = std::make_unique<Node>(anode.mName.C_Str());
		break;
	case 1:
		pNode = std::make_unique<MeshInstance>(meshPtrs.at(anode.mMeshes[0]), anode.mName.C_Str());
		break;
	default:
		pNode = std::make_unique<Node>(anode.mName.C_Str());
		for (unsigned int i = 0; i < anode.mNumMeshes; i++)
		{
			auto& mesh = meshPtrs.at(anode.mMeshes[i]);
			pNode->AddChild(std::make_unique<MeshInstance>(mesh, aiMeshes[i]->mName.C_Str()));
		}
	}

	pNode->SetTransform(Transform(float3{ pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z }, { scaling.x, scaling.y, scaling.z }));

	for (unsigned int i = 0; i < anode.mNumChildren; i++)
	{
		pNode->AddChild(ParseNode(*anode.mChildren[i], meshPtrs, aiMeshes));
	}

	return pNode;
}
