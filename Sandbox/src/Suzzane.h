#pragma once

#include "Nodes/MeshInstance.h"
#include "Nodes/PointLight.h"
#include "Drawables/PhongDrawable.h"

class Suzzane : public MeshInstance
{
public:
	Suzzane(Graphics& gfx, float speed, const std::string& name, PointLight& light)
		:
		MeshInstance(std::make_shared<PhongDrawable>(gfx, IndexedTriangleList("Models\\suzanne.obj"),
			PhongDrawable::Material{ {1.0f, 1.0f, 1.0f}, 4.0f, 100.0f }), name),
		speed(speed)
	{
		PhongDrawable& mesh = static_cast<PhongDrawable&>(Mesh());
		mesh.SetLight(light);
	}
	void _Update(float dt) override
	{
		SetTransform(GetTransform().Rotate(float3{ speed * std::sin(dt),
												   speed * std::sin(dt * 2),
												   dt * std::sin(speed / 2)}).
												   WrapRotation());
	}
private:
	float speed;
};
