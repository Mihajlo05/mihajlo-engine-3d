#include "Node.h"
#include "Math/MihajloMath.h"
#include "Gui/imgui/imgui.h"

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

void Node::RenderGuiTree() const
{
	if (ImGui::TreeNode(name.c_str()))
	{
		for (const auto& pChild : childrens)
		{
			pChild->RenderGuiTree();
		}
		ImGui::TreePop();
	}
}
