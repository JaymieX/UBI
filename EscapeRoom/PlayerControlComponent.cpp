#include "stdafx.h"
#include "PlayerControlComponent.h"
#include "SceneSystem.h"

EscapeRoom::PlayerControlComponent::PlayerControlComponent(GameObject* owner_, float speed_) :
IComponent(owner_, GameTypeGUID::GetGUID<PlayerControlComponent>()),
speed(speed_)
{
}

void EscapeRoom::PlayerControlComponent::UpdateComponent()
{
	if (freeze_movement) return;
	
	const float displacement = speed * SceneSystem::GetDeltaTime();
	
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		owner->velocity.x = displacement;
		owner->velocity.y = 0;
	}
	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		owner->velocity.x = -displacement;
		owner->velocity.y = 0;
	}
	else if(App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		owner->velocity.x = 0;
		owner->velocity.y = -displacement;
	}
	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		owner->velocity.x = 0;
		owner->velocity.y = displacement;
	}
}
