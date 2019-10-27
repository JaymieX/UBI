#pragma once
#include "IComponent.h"

namespace EscapeRoom
{
	class ShapeAnimatorComponent : public IComponent
	{
		float speed;
		float rad_counter;
		
	public:
		ShapeAnimatorComponent(GameObject* owner_, float speed_);
		void UpdateComponent() override;
	};
}