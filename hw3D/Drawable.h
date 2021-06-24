#pragma once

#include <vector>
#include "Bindable.h"
#include "IndexBuffer.h"
#include <DirectXMath.h>
#include <memory>

class Drawable
{
public:
	Drawable() = default;
	void Draw(Graphics& gfx) const;
	virtual void Update(float dt) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const = 0;
	void AddBindable(std::unique_ptr<Bindable> pBindable);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> pib);
	virtual ~Drawable() = default;
private:
	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> bindablePtrs;
};