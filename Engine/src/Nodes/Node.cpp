#include "Node.h"
#include "Math/MihajloMath.h"
#include "Gui/imgui/imgui.h"
#include "Gui/Inspector.h"

Node::Node(const std::string& name)
	:
	name(name),
	prevTranfs(DirectX::XMMatrixIdentity())
{ }

void Node::AddChild(std::unique_ptr<Node> node)
{
	assert(node.get() != nullptr);
	childrens.push_back(std::move(node));
}

Transform Node::GetTransform() const
{
	return transf;
}

void Node::SetTransform(const Transform& transf)
{
	this->transf = transf;
}

void Node::HandleMouseEvents(const Mouse::Event& e)
{
	for (auto& pChild : childrens)
	{
		pChild->_HandleMouseEvents(e);
	}
	for (auto& pChild : childrens)
	{
		pChild->HandleMouseEvents(e);
	}
}

void Node::HandleKeyboardEvents(const Keyboard::Event& e)
{
	for (auto& pChild : childrens)
	{
		pChild->_HandleKeyboardEvents(e);
	}
	for (auto& pChild : childrens)
	{
		pChild->HandleKeyboardEvents(e);
	}
}

void Node::Update(float dt)
{
	matrix nextPrevTransf = transf.GetMatrix() * prevTranfs;
	for (auto& pChild : childrens)
	{
		pChild->SetPrevTranfs(nextPrevTransf);
		pChild->_Update(dt);
	}
	for (auto& pChild : childrens)
	{
		pChild->Update(dt);
	}
}

void Node::Draw(Graphics& gfx) const
{
	for (auto& pChild : childrens)
	{
		pChild->_Draw(gfx);
	}
	for (auto& pChild : childrens)
	{
		pChild->Draw(gfx);
	}
}

void Node::_HandleMouseEvents(const Mouse::Event& e)
{
}

void Node::_HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void Node::_Update(float dt)
{
}

void Node::_Draw(Graphics& gfx) const
{
}

void Node::SetPrevTranfs(fmatrix prevTranfs)
{
	this->prevTranfs = prevTranfs;
}

void Node::ShowOnInspector()
{
	float3 pos;
	DirectX::XMStoreFloat3(&pos, transf.pos);
	float3 rot;
	DirectX::XMStoreFloat3(&rot, transf.rot);
	float3 scale;
	DirectX::XMStoreFloat3(&scale, transf.scale);
	ImGui::InputFloat3("Pozicija", &pos.x);

	ImGui::Text("Rotacija");
	ImGui::SliderAngle("Roll", &rot.z);
	ImGui::SliderAngle("Pitch", &rot.x);
	ImGui::SliderAngle("Yaw", &rot.y);

	ImGui::InputFloat3("Scale", &scale.x);

	transf.pos = DirectX::XMLoadFloat3(&pos);
	transf.rot = DirectX::XMLoadFloat3(&rot);
	transf.scale = DirectX::XMLoadFloat3(&scale);
}

void Node::RenderGuiTree(int& indexTracker, std::optional<int>& selectedIndex, Node*& pSelectedNode)
{
	int curIndex = indexTracker;
	indexTracker++;

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (childrens.empty()) flags |= ImGuiTreeNodeFlags_Leaf;
	if (curIndex == selectedIndex.value_or(-1)) flags |= ImGuiTreeNodeFlags_Selected;

	if (ImGui::TreeNodeEx(name.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			selectedIndex = curIndex;
			pSelectedNode = this;
		}
		for (const auto& pChild : childrens)
		{
			pChild->RenderGuiTree(indexTracker, selectedIndex, pSelectedNode);
		}
		ImGui::TreePop();
	}
}
