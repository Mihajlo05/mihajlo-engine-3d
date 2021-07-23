#pragma once

#include "Nodes/Node.h"
#include "Drawables/Drawable.h"
#include "Math/IndexedTriangleList.h"
#include "assimp.h"

class MeshInstance : public Node
{
public:
	MeshInstance(Graphics& gfx, const IndexedTriangleList& itl, const std::string& name);
	MeshInstance(std::shared_ptr<Drawable> pMesh, const std::string& name);
	virtual ~MeshInstance() = default;
private:
	void _Draw(Graphics& gfx) const override;
private:
	std::shared_ptr<Drawable> pMesh;
};