#pragma once

#include "ICamera.h"
#include "Math/Transform.h"
#include "Windows/Keyboard.h"
#include "Windows/Mouse.h"

class EditorCamera : public ICamera
{
public:
	EditorCamera(float aspectRation);
	EditorCamera(Transform transf, float aspectRation);
	EditorCamera(Transform transf, fmatrix proj);
	matrix GetView() const  override;
	matrix GetProjection() const override;
	matrix GetViewProjection() const override;
	void SetProjection(fmatrix proj) override;
	Transform GetTransform() const;
	void SetTransform(const Transform& transf);
	void HandleMouseInput(const Mouse::Event& e);
	void Update(float dt, Keyboard& kbd);
private:
	matrix proj;
	Transform transf;
	float rotSpeed = 0.3f;
	float travelSpeed = 10.0f;
};

