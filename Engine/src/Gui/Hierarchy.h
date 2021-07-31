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
		void BeginFrame();
		void EndFrame(float2 rndPos, float2 rndSize, ICamera& cam);
		void SetRoot(Node& node);
		const Node* GetRoot() const;
		Node* GetSelectedNode();
		const Node* GetSelectedNode() const;
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