#pragma once

#include <vector>
#include "Math/MihajloMath.h"
#include "Drawables/Drawable.h"
#include <assimp/scene.h>

class Model
{
private:
	class Node
	{
		friend Model;
	public:
		Node(const std::vector<Drawable*>& meshPtrs, fmatrix transf, const std::string& name);
		void Draw(Graphics& gfx, fmatrix prevTransfs) const;
	private:
		void AddChild(const Node& node);
		void SpawnNodeTree() const;
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
private:
	static std::unique_ptr<Drawable> ParseMesh(const aiMesh& amesh, Graphics& gfx);
	std::unique_ptr<Node> ParseNode(const aiNode& anode);
private:
	std::vector<std::unique_ptr<Drawable>> meshPtrs;
	std::unique_ptr<Node> pRoot;
	matrix transf;
};