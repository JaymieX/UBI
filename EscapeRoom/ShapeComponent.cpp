#include "stdafx.h"
#include "ShapeComponent.h"

EscapeRoom::ShapeComponent::ShapeComponent(GameObject* owner_, LinePack&& lines_, MathVector&& color_) :
IComponent(owner_, GameTypeGUID::GetGUID<ShapeComponent>()),
lines(lines_),
color(color_)
{
}

void EscapeRoom::ShapeComponent::RenderComponent()
{
	for (auto& line : lines)
	{
		GameObject::DrawLine(owner->transform, line, color.x, color.y, color.z);
	}
}
