#pragma once

#include "Graphics/Graphics.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace Binds
{
	class Bindable;

	class Codex
	{
	public:
		template<class B, typename... Params>
		static std::shared_ptr<B> Resolve(Graphics& gfx, Params&&... params)
		{
			return Get()._Resolve<B>(gfx, std::forward<Params>(params)...);
		}
	private:
		template<class B, typename... Params>
		std::shared_ptr<B> _Resolve(Graphics& gfx, Params&&... params)
		{
			std::string key = B::GenerateUID(std::forward<Params>(params)...);
			auto i = bindables.find(key);
			if (i == bindables.end())
			{
				auto bind = std::make_shared<B>(gfx, std::forward<Params>(params)...);
				bindables[key] = bind;
				return std::move(bind);
			}
			else
			{
				return std::static_pointer_cast<B>(i->second);
			}
		}
		static Codex& Get()
		{
			static Codex codex;
			return codex;
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<Bindable>> bindables;
	};
}