#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class PlayerControlComponent : public IComponent
	{
	private:
		float speed;

		void CollisionEnterCallBack(GameObject* object_);
		
	public:
		MathVector velocity;
		bool freeze_movement = false;
		
		PlayerControlComponent(GameObject* owner_, float speed_);
		
		void UpdateComponent() override;
		void StartComponent() override;
	};
}
