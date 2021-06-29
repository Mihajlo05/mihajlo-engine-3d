#pragma once

#include "DrawableBase.h"
#include "AllBindables.h"
#include <memory>
#include <random>

struct PBuf
{
	float time, t1, t2, t3;
};

class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx);
	void Update(float dt, Graphics& gfx) override;
	DirectX::XMMATRIX GetTransformation() const;
private:
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float dpitch = 3.14f / 3.0f;
	float dyaw = 2.1f / 3.0f;
	float droll = 6.28f / 3.0f;

	float time = 0.0f;
	static PixelConstantBuffer<PBuf>* pcb;
};