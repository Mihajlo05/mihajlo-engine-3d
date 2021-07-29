#pragma once

#include "Nodes/MeshInstance.h"
#include "Nodes/PointLight.h"
#include "Drawables/Phong.h"

class Suzzane : public MeshInstance
{
private:
	using Phong = Drawables::Phong;
public:
	Suzzane(Graphics& gfx, float speed, const std::string& name, PointLight& light)
		:
		MeshInstance(std::make_shared<Phong>(gfx, IndexedTriangleList("Models\\suzanne.obj"),
			Phong::Material{ {1.0f, 1.0f, 1.0f}, 4.0f, 100.0f }), name),
		speed(speed)
	{
		Phong& mesh = static_cast<Phong&>(Mesh());
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
