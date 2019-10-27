#pragma once

#include "SceneSystem.h"

#include "PlayerControlComponent.h"
#include "ShapeComponent.h"
#include "ShapeAnimatorComponent.h"
#include "PlayerControlComponent.h"
#include "SpriteComponent.h"

#define WALL_THICKNESS 10.f

namespace EscapeRoom
{
	class EscapeRoomLevelScene : public IScene
	{
	protected:
		Rect base_box{ MathVector(0.f, 0.f), 1.f, 1.f };
		MathVector player_start;
		
		GameObject* player_object;

		PlayerControlComponent* player_controller;

		void PlayerCollidedEnter(GameObject* other_);
		
		void MakeWallObject(MathVector&& position_, const float width_, const float height_);

		GameObject* MakeKillerObjectB(MathVector&& position_);
		GameObject* MakeKillerObjectA(MathVector&& position_);

		void MakePlatformObject(MathVector&& start_, MathVector&& end_, MathVector&& scale_);

		void MakeExitObject(MathVector&& position_);

		void MakePlayer(const MathVector& position_);
	};
}
