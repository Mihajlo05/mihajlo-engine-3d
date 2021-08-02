#pragma once

#include "Nodes/Node.h"
#include "Graphics/Graphics.h"
#include "Inspector.h"
#include "Gizmos.h"
#include <optional>

namespace Gui
{
	class Hierarchy
	{
	public:
		Hierarchy(Graphics& gfx);
		void BeginFrame();
		void EndFrame();
		void SetRoot(Node& node);
		const Node* GetRoot() const;
	private:
		Node* pRoot = nullptr;
		Node* pSelectedNode = nullptr;
		Inspector inspector;
		Gizmos gizmos;
		Graphics& gfx;
	public:
		static constexpr const char* wndName = "Hijerarhija";
	};
}