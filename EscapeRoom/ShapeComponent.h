#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class ShapeComponent : public IComponent
	{
	private:
		LinePack lines;
		MathVector color;
		
	public:
		ShapeComponent(GameObject* owner_, LinePack&& lines_, MathVector&& color_);
		
		void RenderComponent() override;
	};
}
