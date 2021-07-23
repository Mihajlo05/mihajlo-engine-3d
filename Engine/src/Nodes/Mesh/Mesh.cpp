#include "Mesh.h"
#include "Drawables/PhongDrawable.h"

MeshInstance::MeshInstance(Graphics& gfx, const IndexedTriangleList& itl, const std::string& name)
	:
	Node(name)
{
	pMesh = std::make_unique<PhongDrawable>(gfx,
		itl,
		PhongDrawable::Material{ {1.0f, 1.0f, 1.0f}, 4.0f, 100.0f });
}

void MeshInstance::_Draw(Graphics& gfx) const
{
	matrix globalTransf = GetTransform().GetMatrix() * GetPrevTranfs();

	pMesh->SetTransformation(globalTransf);
	pMesh->Draw(gfx);

	for (const auto& pChild : childrens)
	{
		MeshInstance& child = *static_cast<MeshInstance*>(pChild.get());
		child._Draw(gfx);
	}
}