#include "Drawable.h"

using namespace Binds;

namespace Drawables
{
	void Drawable::Draw(Graphics& gfx) const
	{
		for (const auto& pb : bindablePtrs)
		{
			pb->Bind(gfx);
		}

		gfx.DrawIndexed(pIndexBuffer->GetCount());
	}

	void Drawable::ResetTransformations()
	{
		transformation = DirectX::XMMatrixIdentity();
	}

	void Drawable::Transform(fmatrix t)
	{
		transformation *= t;
	}

	void Drawable::SetTransformation(fmatrix t)
	{
		transformation = t;
	}

	matrix Drawable::GetTransformation() const
	{
		return transformation;
	}

	void Drawable::AddBind(std::shared_ptr<Bindable> pBindable)
	{
		if (typeid(*pBindable) == typeid(IndexBuffer))
		{
			assert(!pIndexBuffer);
			pIndexBuffer = static_cast<IndexBuffer*>(pBindable.get());
		}
		bindablePtrs.push_back(std::move(pBindable));
	}
}