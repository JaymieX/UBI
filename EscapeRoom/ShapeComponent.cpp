#include "stdafx.h"
#include "ShapeComponent.h"

EscapeRoom::ShapeComponent::ShapeComponent(GameObject* owner_, LinePack&& lines_, MathVector&& color_) :
IComponent(owner_, GameTypeGUID::GetGUID<ShapeComponent>()),
lines(lines_),
color(color_)
{
}

void EscapeRoom::ShapeComponent::UpdateComponent()
{
}

void EscapeRoom::ShapeComponent::RenderComponent()
{
	GameObject::DrawLine(owner->transform, lines.at(0), color.x, color.y, color.z);
	GameObject::DrawLine(owner->transform, lines.at(1), color.x, color.y, color.z);
	GameObject::DrawLine(owner->transform, lines.at(2), color.x, color.y, color.z);
	GameObject::DrawLine(owner->transform, lines.at(3), color.x, color.y, color.z);
}
