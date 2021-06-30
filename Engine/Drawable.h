#pragma once

#include <vector>
#include "Bindable.h"
#include "IndexBuffer.h"
#include <DirectXMath.h>
#include <memory>

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable(Graphics& gfx);
	virtual void Draw() const;
	virtual void Update(float dt) = 0;
	void ResetTransformations();
	void AddTransformation(DirectX::FXMMATRIX t);
	DirectX::XMMATRIX GetTransformation() const;
	virtual ~Drawable() = default;
protected:
	void AddBindable(std::unique_ptr<Bindable> pBindable);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> pib);
protected:
	Graphics& gfx;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> bindablePtrs;
	DirectX::XMMATRIX transformation = DirectX::XMMatrixIdentity();
};