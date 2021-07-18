#pragma once

#include "Drawable.h"

template<class T>
class DrawableBase : public Drawable
{
public:
	void Draw(Graphics& gfx) const override
	{
		for (auto& b : staticBindablePtrs)
		{
			b->Bind(gfx);
		}
		Drawable::Draw(gfx);
	}
protected:
	DrawableBase() = default;
	bool IsStaticInitialized() const
	{
		return !staticBindablePtrs.empty();
	}
	void AddStaticBindable(std::unique_ptr<Bindable> b)
	{
		assert(typeid(b) != typeid(IndexBuffer));
		staticBindablePtrs.push_back(std::move(b));
	}
	template<class B, typename... Params>
	void AddStaticBindable(Params&&... params)
	{
		AddStaticBindable(std::make_unique<B>(std::forward<Params>(params)...));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ib)
	{
		assert(pIndexBuffer == nullptr);
		pIndexBuffer = ib.get();
		staticBindablePtrs.push_back(std::move(ib));
	}
	template<typename... Params>
	void AddStaticIndexBuffer(Params&&... params)
	{
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(std::forward<Params>(params)...));
	}
	void AddIndexBufferFromStatic()
	{
		assert(pIndexBuffer == nullptr);
		bool found = false;
		for (const auto& b : staticBindablePtrs)
		{
			if (const IndexBuffer* pib = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuffer = pib;
				found = true;
				break;
			}
		}
		assert(found);
	}
	virtual ~DrawableBase() = default;
private:
	static std::vector<std::unique_ptr<Bindable>> staticBindablePtrs;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBindablePtrs;
