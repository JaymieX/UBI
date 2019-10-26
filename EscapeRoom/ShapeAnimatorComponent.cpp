#include "stdafx.h"
#include "ShapeAnimatorComponent.h"
#include "SceneSystem.h"

#define ACC_E 0.01f

#define  TARGET_MAX true
#define  TARGET_MIN false

EscapeRoom::ShapeAnimatorComponent::ShapeAnimatorComponent(GameObject* owner_, float min_, float max_,
	float speed_) :
	IComponent(owner_, GameTypeGUID::GetGUID<ShapeAnimatorComponent>()),
	min_trans(min_),
	max_trans(max_),
	speed(speed_),
	current_trans(min_),
	target_id(TARGET_MAX)
{
}

void EscapeRoom::ShapeAnimatorComponent::UpdateComponent()
{
	owner->scale = MathVector(current_trans, current_trans);
	bool swap = true;

	if (target_id == TARGET_MAX)
	{
		if (current_trans < max_trans)
		{
			current_trans += speed * SceneSystem::GetDeltaTime();
			swap = false;
		}
	}
	else
	{
		if (current_trans > min_trans)
		{
			current_trans -= speed * SceneSystem::GetDeltaTime();
			swap = false;
		}
	}
	
	if (swap)
	{
		target_id = !target_id;
	}
}
