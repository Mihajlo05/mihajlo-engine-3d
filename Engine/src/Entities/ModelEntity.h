#pragma once

#include "Entity.h"
#include "Model/Model.h"

class ModelEntity : public Entity
{
public:
	ModelEntity(Graphics& gfx, const std::string& filename)
		:
		model(gfx, filename)
	{ }
	void Draw(Graphics& gfx) override
	{
		model.SetTransform(GetTransform().GetMatrix());
		model.Draw(gfx);
	}
	void SpawnControllWindow(const std::string& wndName) override
	{
		Entity::SpawnControllWindow(wndName);
		model.SpawnNodeTree(wndName);
	}
private:
	Model model;
};