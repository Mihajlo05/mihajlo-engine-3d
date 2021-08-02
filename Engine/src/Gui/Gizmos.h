#pragma once

#include "Graphics/Graphics.h"
#include "Nodes/Node.h"

namespace Gui
{
	class Gizmos
	{
	public:
		Gizmos(Graphics& gfx);
		void SetNode(Node* pn);
		void BeginFrame();
		void EndFrame();
	private:
		Graphics& gfx;
		Node* pNode = nullptr;
		int operation = 7;
	};
}
