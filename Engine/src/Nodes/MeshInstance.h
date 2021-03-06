#pragma once

#include "Nodes/Node.h"
#include "Drawables/Drawable.h"
#include "Math/IndexedTriangleList.h"
#include "assimp.h"

class MeshInstance : public Node
{
public:
	MeshInstance(std::shared_ptr<Drawables::Drawable> pMesh, const std::string& name);
	virtual ~MeshInstance() = default;
	Drawables::Drawable& Mesh()
	{
		assert(pMesh != nullptr);
		return *pMesh;
	}
private:
	void _Draw(Graphics& gfx) const override;
private:
	std::shared_ptr<Drawables::Drawable> pMesh;
};