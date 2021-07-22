#include "Model.h"
#include "Math/IndexedTriangleList.h"
#include "Drawables/PhongDrawable.h"
#include "imgui/imgui.h"

Model::Node::Node(const std::vector<Drawable*>& meshPtrs, fmatrix transf, const std::string& name)
	:
	meshPtrs(meshPtrs),
	transf(transf),
	name(name)
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

std::string Model::Node::GetName() const
{
	return name;
}

void Model::Node::SetName(const std::string& name)
{
	this->name = name;
}

void Model::Node::AddChild(const Node& node)
{
	childs.push_back(node);
}

void Model::Node::SpawnNodeTree(int& nodeIndexTracker, std::optional<int>& selectedIndex, Node*& pSelectedNode) const
{
	int curIndex = nodeIndexTracker;
	nodeIndexTracker++;

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (curIndex == selectedIndex.value_or(-1))
	{
		flags |= ImGuiTreeNodeFlags_Selected;
		pSelectedNode = const_cast<Node*>(this);
	}
	if (childs.empty()) flags |= ImGuiTreeNodeFlags_Leaf;

	if (ImGui::TreeNodeEx(name.c_str(), flags))
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			selectedIndex = curIndex;
		}

		for (const auto& node : childs)
		{
			node.SpawnNodeTree(nodeIndexTracker, selectedIndex, pSelectedNode);
		}
		ImGui::TreePop();
	}
}

Model::Model(Graphics& gfx, const std::string& filename)
{
	transf = DirectX::XMMatrixIdentity();

	Assimp::Importer imp;
	const aiScene* pModel = imp.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	assert(pModel != nullptr);

	meshPtrs.reserve(pModel->mNumMeshes);
	for (int i = 0; i < (int)pModel->mNumMeshes; i++)
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

void Model::SpawnNodeTree(const std::string& wndName) const
{
	if (ImGui::Begin(wndName.c_str()))
	{
		pSelectedNode = nullptr;
		int nodeIndexTracker = 0;
		pRoot->SpawnNodeTree(nodeIndexTracker, selectedNodeIndex, pSelectedNode);
	}
	ImGui::End();
}

bool Model::IsAnyNodeSelected() const
{
	return pSelectedNode != nullptr;
}

Model::Node& Model::SelectedNode()
{
	assert(IsAnyNodeSelected());
	return *pSelectedNode;
}

const Model::Node& Model::SelectedNode() const
{
	assert(IsAnyNodeSelected());
	return *pSelectedNode;
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
	for (int i = 0; i < (int)anode.mNumMeshes; i++)
	{
		curMeshPtrs.push_back(meshPtrs.at(anode.mMeshes[i]).get());
	}

	auto pNode = std::make_unique<Node>(curMeshPtrs, transf, anode.mName.C_Str());

	for (int i = 0; i < (int)anode.mNumChildren; i++)
	{
		pNode->AddChild(*ParseNode(*anode.mChildren[i]));
	}

	return pNode;
} 
