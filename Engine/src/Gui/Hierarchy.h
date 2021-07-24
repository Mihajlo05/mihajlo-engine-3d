#pragma once

#include "Nodes/Node.h"
#include "Inspector.h"
#include <optional>

namespace Gui
{
	class Hierarchy
	{
	public:
		void SpawnWindow();
		void SetRoot(Node& node);
		const Node* GetRoot() const;
	private:
		Node* pRoot = nullptr;
		Node* pSelectedNode = nullptr;
		Inspector inspector;
	public:
		static constexpr const char* wndName = "Hijerarhija";
	};
}