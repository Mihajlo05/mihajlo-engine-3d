#pragma once

#include <vector>
#include "Bindables/Bindable.h"
#include "Bindables/IndexBuffer.h"
#include "Math/MihajloMath.h"
#include <memory>

namespace Drawables
{
	class Drawable
	{
	public:
		virtual void Draw(Graphics& gfx) const;
		virtual void Update(float dt) {}
		void ResetTransformations();
		void Transform(fmatrix t);
		void SetTransformation(fmatrix t);
		matrix GetTransformation() const;
		virtual ~Drawable() = default;
	protected:
		Drawable() = default;
		void AddBind(std::shared_ptr<Binds::Bindable> pBindable);
	private:
		const Binds::IndexBuffer* pIndexBuffer = nullptr;
		std::vector<std::shared_ptr<Binds::Bindable>> bindablePtrs;
		matrix transformation = DirectX::XMMatrixIdentity();
	};
}
