#pragma once

#include "Entity.h"
#include "Model/Model.h"

class ModelEntity : public Entity
{
public:
	ModelEntity(Graphics& gfx, const std::string& filename, const std::string& name)
		:
		Entity(name),
		model(gfx, filename)
	{ }
	void Draw(Graphics& gfx) override
	{
		model.SetTransform(GetTransform().GetMatrix());
		model.Draw(gfx);
	}
	void SpawnControllWindow() override
	{
		Entity::SpawnControllWindow();
		model.SpawnNodeTree(GetName());
	}
private:
	Model model;
};