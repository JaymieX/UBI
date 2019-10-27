#pragma once

#include "SceneSystem.h"
#include "PlayerControlComponent.h"

namespace EscapeRoom
{
	class SceneLevel0 : public IScene
	{
	private:
		GameObject* boundary;
		GameObject* player_object;

		std::vector<GameObject*> wall_objects;

		PlayerControlComponent* player_controller;

		bool debug_collided = false;

		void PlayerCollidedEnter(GameObject* other_);
		void PlayerCollidedExit(GameObject* other_);

		MathVector player_start;

		void MakeWallObject(MathVector&& position_, const float width_, const float height_);

		GameObject* MakeKillerObjectB(MathVector&& position_);
		GameObject* MakekillerObjectA(MathVector&& position_);
		
	public:
		void StartScene() override;
		
		void UpdateScene() override;
		
		void RenderScene() override;
		
		void EndScene() override;
	};
}
