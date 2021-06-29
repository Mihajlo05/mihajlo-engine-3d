#include "Drawable.h"

Drawable::Drawable(Graphics& gfx)
	:
	gfx(gfx)
{ }

void Drawable::Draw() const
{
	for (const auto& pb : bindablePtrs)
	{
		pb->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBindable(std::unique_ptr<Bindable> pBindable)
{
	assert("Can't add index buffer in AddBindable function, you MUST use AddIndexBuffer" &&
		typeid(*pBindable) != typeid(IndexBuffer));
	bindablePtrs.push_back(std::move(pBindable));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> pib)
{
	assert("Binding index buffer second time, this is not allowed" && pIndexBuffer == nullptr);
	pIndexBuffer = pib.get();
	bindablePtrs.push_back(std::move(pib));
}