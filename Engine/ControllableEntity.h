#pragma once

#include "Entity.h"
#include "Drawable.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <memory>
#include <string>

class ControllableEntity : public Entity
{
public:
	ControllableEntity(std::unique_ptr<Drawable> model, const std::string& name, DirectX::XMFLOAT3 pos);
	ControllableEntity(const ControllableEntity& other) = delete;
	ControllableEntity& operator=(const ControllableEntity& other) = delete;
	ControllableEntity(ControllableEntity&&) = default;
	ControllableEntity& operator=(ControllableEntity&&) = default;
	~ControllableEntity() = default;

	void Update(float dt, Keyboard& kbd, Mouse& mouse) override;
	void Draw() const override;
private:
	std::unique_ptr<Drawable> pModel;
	std::string name;
};