#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class PathControlComponent : public IComponent
	{
	private:
		Points points;
		MathVector* current_target;
		size_t index;
		int strif;

		float speed;
		
	public:
		PathControlComponent(GameObject* owner_, Points&& points_, float speed_);
		
		void UpdateComponent() override;
	};
}