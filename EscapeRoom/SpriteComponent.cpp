#include "stdafx.h"
#include "SpriteComponent.h"

EscapeRoom::SpriteComponent::SpriteComponent(GameObject* owner_, std::string&& path_) :
	IComponent(owner_, GameTypeGUID::GetGUID<SpriteComponent>()),
	sprite(std::make_unique<CSimpleSprite>(path_.c_str()))
{
}

void EscapeRoom::SpriteComponent::RenderComponent()
{
	const MathVector owner_pos		= owner->GetPosition();
	const MathVector owner_scale	= owner->GetScale();
	
	sprite->SetPosition	(owner_pos.x, owner_pos.y);
	sprite->SetScale	(owner_scale.x);
	
	sprite->Draw();
}
