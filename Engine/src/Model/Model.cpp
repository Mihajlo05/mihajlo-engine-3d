#include "Model.h"
#include "Math/IndexedTriangleList.h"
#include "Drawables/PhongDrawable.h"

Model::Node::Node(const std::vector<Drawable*>& meshPtrs, fmatrix transf)
	:
	meshPtrs(meshPtrs),
	transf(transf)
{ }

void Model::Node::Draw(Graphics& gfx, fmatrix prevTransfs) const
{
	matrix built = transf * prevTransfs;

	for (const auto& pm : meshPtrs)
	{
		pm->SetTransformation(built);
		pm->Draw(gfx);
	}
	for (const auto& c : childs)
	{
		c.Draw(gfx, built);
	}
}

void Model::Node::AddChild(const Node& node)
{
	childs.push_back(node);
}

Model::Model(Graphics& gfx, const std::string& filename)
{
	transf = DirectX::XMMatrixIdentity();

	Assimp::Importer imp;
	const aiScene* pModel = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	assert(pModel != nullptr);

	meshPtrs.reserve(pModel->mNumMeshes);
	for (int i = 0; i < pModel->mNumMeshes; i++)
	{
		meshPtrs.push_back(ParseMesh(*pModel->mMeshes[i], gfx));
	}

	pRoot = ParseNode(*pModel->mRootNode);
}

void Model::Draw(Graphics& gfx) const
{
	pRoot->Draw(gfx, transf);
}

void Model::SetTransform(fmatrix t)
{
	transf = t;
}

void Model::Transform(fmatrix t)
{
	transf *= t;
}

matrix Model::GetTransform() const
{
	return transf;
}

std::unique_ptr<Drawable> Model::ParseMesh(const aiMesh& amesh, Graphics& gfx)
{
	IndexedTriangleList itl = amesh;
	return std::make_unique<PhongDrawable>(gfx, itl, PhongDrawable::Material{ {1.0f, 1.0f, 1.0f}, 5.0f, 100.0f });
}

std::unique_ptr<Model::Node> Model::ParseNode(const aiNode& anode)
{
	namespace dx = DirectX;

	matrix transf = dx::XMMatrixTranspose(*reinterpret_cast<fmatrix*>(&anode.mTransformation));

	std::vector<Drawable*> curMeshPtrs;
	curMeshPtrs.reserve(anode.mNumMeshes);
	for (int i = 0; i < anode.mNumMeshes; i++)
	{
		curMeshPtrs.push_back(meshPtrs.at(anode.mMeshes[i]).get());
	}

	auto pNode = std::make_unique<Node>(curMeshPtrs, transf);

	for (int i = 0; i < anode.mNumChildren; i++)
	{
		pNode->AddChild(*ParseNode(*anode.mChildren[i]));
	}

	return pNode;
} 
