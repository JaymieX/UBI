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

		float scale_x, scale_y;

		void MakeWallObject(MathVector&& position_, const float width_, const float height_);
		
	public:
		void StartScene() override;
		
		void UpdateScene() override;
		
		void RenderScene() override;
		
		void EndScene() override;
	};
}
