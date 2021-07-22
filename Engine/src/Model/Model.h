#pragma once

#include <vector>
#include "Math/MihajloMath.h"
#include "Drawables/Drawable.h"
#include <assimp/scene.h>
#include <optional>

class Model
{
public:
	class Node
	{
		friend Model;
	public:
		Node(const std::vector<Drawable*>& meshPtrs, fmatrix transf, const std::string& name);
		void Draw(Graphics& gfx, fmatrix prevTransfs) const;
		std::string GetName() const;
		void SetName(const std::string& name);
	private:
		void AddChild(const Node& node);
		void SpawnNodeTree(int& nodeIndexTracker, std::optional<int>& selectedIndex, Node*& pSelectedNode) const;
	private:
		std::vector<Drawable*> meshPtrs;
		std::vector<Node> childs;
		matrix transf;
		std::string name;
	};
public:
	Model(Graphics& gfx, const std::string& filename);
	void Draw(Graphics& gfx) const;
	void SetTransform(fmatrix t);
	void Transform(fmatrix t);
	matrix GetTransform() const;
	void SpawnNodeTree(const std::string& wndName) const;
	bool IsAnyNodeSelected() const;
	Node& SelectedNode();
	const Node& SelectedNode() const;
private:
	static std::unique_ptr<Drawable> ParseMesh(const aiMesh& amesh, Graphics& gfx);
	std::unique_ptr<Node> ParseNode(const aiNode& anode);
private:
	std::vector<std::unique_ptr<Drawable>> meshPtrs;
	std::unique_ptr<Node> pRoot;
	matrix transf;
	mutable Node* pSelectedNode = nullptr;
	mutable std::optional<int> selectedNodeIndex = {};
};