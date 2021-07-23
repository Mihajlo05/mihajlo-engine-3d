#pragma once

#include "Math/Transform.h"
#include <vector>
#include <string>
#include <memory>
#include "Windows/Mouse.h"
#include "Windows/Keyboard.h"
#include "Graphics/Graphics.h"

class Node
{
private:
	using ChildrenList = std::vector<std::unique_ptr<Node>>;
public:
	Node(const std::string& name);
	void AddChild(std::unique_ptr<Node> node);
	Transform GetTransform() const;
	void SetTransform(const Transform& transf);

	void HandleMouseEvents(const Mouse::Event& e);
	void HandleKeyboardEvents(const Keyboard::Event& e);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	virtual ~Node() = default;
protected:
	virtual void _HandleMouseEvents(const Mouse::Event& e);
	virtual void _HandleKeyboardEvents(const Keyboard::Event& e);
	virtual void _Update(float dt);
	virtual void _Draw(Graphics& gfx) const;
protected:
	void SetPrevTranfs(fmatrix prevTranfs);
	matrix GetPrevTranfs() const { return prevTranfs; }
protected:
	ChildrenList childrens;
private:
	Transform transf;
	matrix prevTranfs;
	std::string name;
};