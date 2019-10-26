#pragma once

#include "IComponent.h"

namespace EscapeRoom
{
	class SpriteComponent : public IComponent
	{
	private:
		std::unique_ptr<CSimpleSprite> sprite;
		
	public:
		SpriteComponent(GameObject* owner_, std::string&& path_);
		
		void RenderComponent() override;
	};
}
