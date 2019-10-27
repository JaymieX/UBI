#include "stdafx.h"
#include "ShapeAnimatorComponent.h"
#include "SceneSystem.h"

EscapeRoom::ShapeAnimatorComponent::ShapeAnimatorComponent(GameObject* owner_, float speed_) :
	IComponent(owner_, GameTypeGUID::GetGUID<ShapeAnimatorComponent>()),
	speed(speed_),
	rad_counter(0.f)
{
	owner->SetRotation(MathVector(0.f, 0.f, 1.f));
}

void EscapeRoom::ShapeAnimatorComponent::UpdateComponent()
{
	rad_counter += speed * SceneSystem::GetDeltaTime();
	owner->SetAngle(rad_counter);
}
