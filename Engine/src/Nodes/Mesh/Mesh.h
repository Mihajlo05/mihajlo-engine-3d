#pragma once

#include "Nodes/Node.h"
#include "Drawables/Drawable.h"
#include "Math/IndexedTriangleList.h"

class MeshInstance : public Node
{
public:
	MeshInstance(Graphics& gfx, const IndexedTriangleList& itl, const std::string& name);
	virtual ~MeshInstance() = default;
private:
	void _Draw(Graphics& gfx) const override;
private:
	std::unique_ptr<Drawable> pMesh;
};