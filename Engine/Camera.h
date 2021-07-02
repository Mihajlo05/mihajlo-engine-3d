#pragma once

#include <DirectXMath.h>

class Camera
{
public:
	void Update(float dt);
	DirectX::XMMATRIX GetTransfForModel() const;
private:
	float r = 1.0f;
	float alpha = 0.0f;
	float beta = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
};