#pragma once

#include "DrawableEntity.h"
#include "Drawables/PhongDrawable.h"
#include "imgui/imgui.h"

class PhongDrawableEntity : public DrawableEntity
{
public:
	PhongDrawableEntity(std::unique_ptr<Drawable> pModel)
		:
		DrawableEntity(std::move(pModel))
	{
		assert(typeid(Model()) == typeid(PhongDrawable&));
	}
	void SpawnControllWindow(const std::string& wndName) override
	{
		DrawableEntity::SpawnControllWindow(wndName);

		PhongDrawable& model = static_cast<PhongDrawable&>(Model());

		if (ImGui::Begin(wndName.c_str()))
		{
			auto material = model.GetMaterial();

			ImGui::ColorPicker3("Boja", &material.color.x);

			ImGui::Text("Spekularni naglasak");
			ImGui::SliderFloat("Intezitet", &material.specularIntensity, 0.0f, 5.0f);
			ImGui::SliderFloat("Stepen", &material.specularPower, 0.0f, 200.0f);

			model.SetMaterial(material);
		}
		ImGui::End();
	}
};