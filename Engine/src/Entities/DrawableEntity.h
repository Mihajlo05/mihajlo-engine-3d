#pragma once

#include "Entity.h"
#include "Drawables/Drawable.h"

class DrawableEntity : public Entity
{
public:
	DrawableEntity(std::unique_ptr<Drawable> pModel)
		:
		pModel(std::move(pModel))
	{ }

	void Draw(Graphics& gfx) override
	{
		pModel->SetTransformation(GetTransform().GetMatrix());
		pModel->Draw(gfx);
	}
protected:
	Drawable& Model()
	{
		return *pModel;
	}
	const Drawable& Model() const
	{
		return *pModel;
	}
private:
	std::unique_ptr<Drawable> pModel;
};