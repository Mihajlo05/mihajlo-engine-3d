#pragma once

#include "Math/Transform.h"
#include <vector>
#include <string>
#include <memory>
#include "Windows/Mouse.h"
#include "Windows/Keyboard.h"
#include "Graphics/Graphics.h"
#include <optional>

namespace Gui
{
	class Hierarchy;
	class Inspector;
}

class Node
{
	friend Gui::Hierarchy;
	friend Gui::Inspector;
public:
	Node(const std::string& name);
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
	void AddChild(std::unique_ptr<Node> node);
	Node* GetChild(const std::string& name);
	const Node* GetChild(const std::string& name) const;
	Transform GetTransform() const;
	void SetTransform(const Transform& transf);
	std::string GetName() const;
	void SetName(const std::string& name);

	void HandleMouseEvents(const Mouse::Event& e);
	void HandleKeyboardEvents(const Keyboard::Event& e);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	virtual ~Node() = default;
private:
	virtual void _HandleMouseEvents(const Mouse::Event& e);
	virtual void _HandleKeyboardEvents(const Keyboard::Event& e);
	virtual void _Update(float dt);
	virtual void _Draw(Graphics& gfx) const;
protected:
	void SetPrevTranfs(fmatrix prevTranfs);
	matrix GetPrevTranfs() const { return prevTranfs; }
protected:
	virtual void ShowOnInspector(); //Used by inspector
private:
	void RenderGuiTree(int& indexTracker, std::optional<int>& selectedIndex, Node*& pSelectedNode); //Used by hierarchy
protected:
	std::vector<std::unique_ptr<Node>> childrens;
private:
	Transform transf;
	matrix prevTranfs;
	std::string name;
};