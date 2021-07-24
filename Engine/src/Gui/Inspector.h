#pragma once

#include "Nodes/Node.h"

namespace Gui
{
	class Inspector
	{
	public:
		void SpawnWindow(Node* pNode);
	public:
		static constexpr const char* wndName = "Pregledac";
	};
}
