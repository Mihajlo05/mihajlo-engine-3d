#include "MeshInstance.h"
#include "Drawables/Phong.h"

using namespace Drawables;

MeshInstance::MeshInstance(std::shared_ptr<Drawable> pMesh, const std::string& name)
	:
	Node(name),
	pMesh(std::move(pMesh))
{
}

void MeshInstance::_Draw(Graphics& gfx) const
{
	pMesh->SetTransformation(GetGlobalTransform().GetMatrix());
	pMesh->Draw(gfx);

	for (const auto& pChild : childrens)
	{
		MeshInstance& child = *static_cast<MeshInstance*>(pChild.get());
		child._Draw(gfx);
	}
}