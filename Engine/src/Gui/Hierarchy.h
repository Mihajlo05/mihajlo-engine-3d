#pragma once

#include "Nodes/Node.h"
#include "Inspector.h"
#include <optional>

namespace Gui
{
	class Hierarchy
	{
	public:
		static Hierarchy& Get()
		{
			static Hierarchy hier;
			return hier;
		}
	public:
		void SpawnWindow();
		void SetRoot(Node& node);
		const Node* GetRoot() const;
	private:
		Hierarchy() = default;
	private:
		Node* pRoot = nullptr;
		Node* pSelectedNode = nullptr;
		Inspector inspector;
	public:
		static constexpr const char* wndName = "Hijerarhija";
	};
}