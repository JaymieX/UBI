#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class PlayerControlComponent : public IComponent
	{
	private:
		float speed;
		
	public:
		bool freeze_movement = false;
		
		PlayerControlComponent(GameObject* owner_, float speed_);
		
		void UpdateComponent() override;
	};
}
