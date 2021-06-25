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
	Drawable() = default;
	virtual void Draw(Graphics& gfx) const;
	virtual void UpdateLogic(float dt) = 0;
	virtual void UpdateGraphics(Graphics& gfx) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const = 0;
	virtual ~Drawable() = default;
protected:
	void AddBindable(std::unique_ptr<Bindable> pBindable);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> pib);
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> bindablePtrs;
};