#pragma once

#include <DirectXMath.h>
#include "Entity.h"
#include "imgui/imgui.h"

class Camera : public Entity
{
public:
	DirectX::XMMATRIX GetView() const
	{
		return GetLocalView();
	}
private:
	DirectX::XMMATRIX GetLocalView() const
	{
		Transform t = GetLocalTransform();

		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, t.rot);

		return DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorScale(t.pos, -1.0f)) *
			DirectX::XMMatrixRotationY(rot.y) * DirectX::XMMatrixRotationX(rot.x) * DirectX::XMMatrixRotationZ(rot.z);
		//Order of roll, pitch, yaw is inversed
	}
};