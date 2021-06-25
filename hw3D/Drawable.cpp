#include "Drawable.h"

void Drawable::Draw(Graphics& gfx) const
{
	for (const auto& pb : bindablePtrs)
	{
		pb->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBindable(std::unique_ptr<Bindable> pBindable)
{
	assert(typeid(*pBindable) != typeid(IndexBuffer));
	bindablePtrs.push_back(std::move(pBindable));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> pib)
{
	assert(pIndexBuffer == nullptr);
	pIndexBuffer = pib.get();
	bindablePtrs.push_back(std::move(pib));
}