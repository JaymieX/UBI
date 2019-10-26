#pragma once
#include "IComponent.h"

namespace EscapeRoom
{
	class ShapeAnimatorComponent : public IComponent
	{
		float min_trans, max_trans;
		float speed;

		float current_trans;
		bool target_id;
		
	public:
		ShapeAnimatorComponent(GameObject* owner_, float min_, float max_, float speed_);
		void UpdateComponent() override;
	};
}