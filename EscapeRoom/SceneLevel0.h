#pragma once

#include "SceneSystem.h"
#include "EscapeRoomLevelScene.h"

namespace EscapeRoom
{
	class SceneLevel0 : public EscapeRoomLevelScene
	{
	public:
		void StartScene() override;
		void ResumeScene() override;
	};
}
