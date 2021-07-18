#pragma once

#include <vector>
#include "Bindables/Bindable.h"
#include "Bindables/IndexBuffer.h"
#include "Math/MihajloMath.h"
#include <memory>

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable(Graphics& gfx);
	virtual void Draw() const;
	virtual void Update(float dt) {}
	void ResetTransformations();
	void AddTransformation(fmatrix t);
	matrix GetTransformation() const;
	virtual ~Drawable() = default;
protected:
	void AddBindable(std::unique_ptr<Bindable> pBindable);
	template<class B, typename... Params>
	void AddBindable(Params&&... params)
	{
		AddBindable(std::make_unique<B>(std::forward<Params>(params)...));
	}
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> pib);
	template<typename... Params>
	void AddIndexBuffer(Params&&... params)
	{
		AddIndexBuffer(std::make_unique<IndexBuffer>(std::forward<Params>(params)...));
	}
protected:
	Graphics& gfx;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> bindablePtrs;
	matrix transformation = DirectX::XMMatrixIdentity();
};
