#include "ControllableEntity.h"
#include "imgui/imgui.h"
#include <DirectXMath.h>

ControllableEntity::ControllableEntity(std::unique_ptr<Drawable> pModel, const std::string& name, DirectX::XMFLOAT3 pos)
	:
	pModel(std::move(pModel)),
	name(name)
{
	SetLocalTransform(GetLocalTransform().Translate(pos));
}

void ControllableEntity::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	SpawnControllWindow(name);
	pModel->ResetTransformations();
	pModel->AddTransformation(GetTransfMatrix());
}

void ControllableEntity::Draw() const
{
	pModel->Draw();
}
