#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class PlayerControlComponent : public IComponent
	{
	private:
		float speed;
		MathVector last_velocity;
		MathVector velocity;
		
	public:
		bool freeze_movement = false;
		
		inline void SetVelocity(const MathVector& value_)
		{
			velocity = value_;
		}

		inline MathVector GetLastVelocity() const
		{
			return last_velocity;
		}
		
		PlayerControlComponent(GameObject* owner_, float speed_);
		
		void UpdateComponent() override;
	};
}
