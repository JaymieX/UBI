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
		velocity.x = displacement;
		velocity.y = 0;

		last_velocity = velocity;
	}
	else if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		velocity.x = -displacement;
		velocity.y = 0;

		last_velocity = velocity;
	}
	else if(App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		velocity.x = 0;
		velocity.y = -displacement;

		last_velocity = velocity;
	}
	else if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		velocity.x = 0;
		velocity.y = displacement;

		last_velocity = velocity;
	}
	
	owner->velocity = velocity;
}
