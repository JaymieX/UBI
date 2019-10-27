#include "stdafx.h"
#include "PlayerControlComponent.h"
#include "SceneSystem.h"
#include "CollisionComponent.h"

void EscapeRoom::PlayerControlComponent::CollisionEnterCallBack(GameObject* object_)
{
	if (!object_->GetComponent<ICollisionComponent>()->GetTrigger())
	{
		velocity = 0.f;
	}
}

EscapeRoom::PlayerControlComponent::PlayerControlComponent(GameObject* owner_, float speed_) :
IComponent(owner_, GameTypeGUID::GetGUID<PlayerControlComponent>()),
speed(speed_)
{
}

void EscapeRoom::PlayerControlComponent::UpdateComponent()
{
	if (freeze_movement) return;

	const float displacement = speed;
	if (owner->velocity.GetMag() <= 0.0f)
	{
		if (App::GetController().GetLeftThumbStickX() > 0.5f)
		{
			velocity.x = displacement;
			velocity.y = 0;
		}
		else if (App::GetController().GetLeftThumbStickX() < -0.5f)
		{
			velocity.x = -displacement;
			velocity.y = 0;
		}
		else if (App::GetController().GetLeftThumbStickY() > 0.5f)
		{
			velocity.x = 0;
			velocity.y = -displacement;
		}
		else if (App::GetController().GetLeftThumbStickY() < -0.5f)
		{
			velocity.x = 0;
			velocity.y = displacement;
		}
	}

	owner->velocity = velocity;
}

void EscapeRoom::PlayerControlComponent::StartComponent()
{
	ICollisionComponent* col = owner->GetComponent<ICollisionComponent>();
	if (col != nullptr)
	{
		col->on_collision_call_backs.Connect(
			this,
			&PlayerControlComponent::CollisionEnterCallBack
		);
	}
}
