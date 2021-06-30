#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	void Update(float dt) override;
	DirectX::XMMATRIX GetTransfForModel() const;
private:
	void Draw() const override;
private:
	float r = 0.0f;
	float alpha = 0.0f;
	float beta = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
};