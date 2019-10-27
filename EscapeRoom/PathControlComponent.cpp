#include "stdafx.h"
#include "PathControlComponent.h"
#include "SceneSystem.h"

EscapeRoom::PathControlComponent::PathControlComponent(GameObject* owner_, Points&& points_, float speed_) :
	IComponent(owner_, GameTypeGUID::GetGUID<PathControlComponent>()),
	points(std::move(points_)),
	current_target(&points.at(0)),
	index(0),
	strif(1),
	speed(speed_)
{
}

void EscapeRoom::PathControlComponent::UpdateComponent()
{
	if (MathVector::VecDistance(owner->GetPosition(), *current_target) > 3.f)
	{
		const MathVector direction = *current_target - owner->GetPosition();
		MathVector movement = direction.GetNormalized() * speed;

		owner->velocity = movement;
	}
	else
	{
		// Switch index
		index += strif;
		if (index >= points.size())
		{
			index = points.size() - 2;
			strif *= -1;
		}
		else if (index == 0)
		{
			strif *= -1;
		}

		current_target = &points.at(index);
	}
}
