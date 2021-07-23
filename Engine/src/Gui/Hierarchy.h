#pragma once
#include "Entities/Entity.h"

namespace Gui
{
	class Hierarchy
	{
	public:
		void GenerateWindow() const;
		void AddEntity(Entity& e);
	public:
		static constexpr const char* wndName = "Hierarhija";
	};
}
