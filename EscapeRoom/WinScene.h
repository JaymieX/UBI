#pragma once
#include "SceneSystem.h"

namespace EscapeRoom
{
	class WinScene : public IScene
	{
	public:
		void UpdateScene() override;
		void RenderScene() override;
	};
}
