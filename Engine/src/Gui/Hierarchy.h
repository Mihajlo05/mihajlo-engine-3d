#pragma once

#include "Nodes/Node.h"

namespace Gui
{
	class Hierarchy
	{
	public:
		void SpawnWindow() const; //not needed if window is not empty, as putting something in the window will also create window
		void SetRoot(Node& node);
		const Node* GetRoot() const;
	private:
		static constexpr const char* wndName = "Hijerarhija";
		Node* pRoot = nullptr;
	};
}