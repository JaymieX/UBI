#include "stdafx.h"
#include "SpriteComponent.h"

EscapeRoom::SpriteComponent::SpriteComponent(GameObject* owner_, std::string&& path_) :
	IComponent(owner_, GameTypeGUID::GetGUID<SpriteComponent>()),
	sprite(std::make_unique<CSimpleSprite>(path_.c_str()))
{
}

void EscapeRoom::SpriteComponent::RenderComponent()
{
	sprite->SetPosition(owner->position.x, owner->position.y);
	sprite->SetScale(owner->scale.x);
	
	sprite->Draw();
}
