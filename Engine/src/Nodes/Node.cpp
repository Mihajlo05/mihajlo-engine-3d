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

Node* Node::GetChild(const std::string& name)
{
	for (auto& c : childrens)
	{
		if (c->GetName() == name)
		{
			return c.get();
		}
	}
	return nullptr;
}

const Node* Node::GetChild(const std::string& name) const
{
	return const_cast<Node*>(this)->GetChild(name);
}

Transform Node::GetTransform() const
{
	return transf;
}

void Node::SetTransform(const Transform& transf)
{
	this->transf = transf;
}

std::string Node::GetName() const
{
	return name;
}

void Node::SetName(const std::string& name)
{
	this->name = name;
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
	for (auto& pChild : childrens)
	{
		pChild->_Update(dt);
	}
	for (auto& pChild : childrens)
	{
		pChild->Update(dt);
	}
}

void Node::Draw(Graphics& gfx) const
{
	matrix nextPrevTransf = transf.GetMatrix() * prevTranfs;
	for (auto& pChild : childrens)
	{
		pChild->SetPrevTranfs(nextPrevTransf);
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
	float3 pos = transf.pos.GetFloat3();
	float3 rot = transf.rot.GetFloat3();
	float3 scale = transf.scale.GetFloat3();
	ImGui::InputFloat3("Pozicija", &pos.x);

	ImGui::Text("Rotacija");
	ImGui::SliderAngle("Roll", &rot.z, -180, 180);
	ImGui::SliderAngle("Pitch", &rot.x, -180, 180);
	ImGui::SliderAngle("Yaw", &rot.y, -180, 180);

	ImGui::InputFloat3("Scale", &scale.x);

	transf = Transform(pos, rot, scale);
}

void Node::RenderGuiTree(Node*& pSelectedNode)
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (childrens.empty()) flags |= ImGuiTreeNodeFlags_Leaf;
	if (pSelectedNode == this) flags |= ImGuiTreeNodeFlags_Selected;

	if (ImGui::TreeNodeEx(name.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			pSelectedNode = this;
		}
		for (const auto& pChild : childrens)
		{
			pChild->RenderGuiTree(pSelectedNode);
		}
		ImGui::TreePop();
	}
}
