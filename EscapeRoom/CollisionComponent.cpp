#include "stdafx.h"
#include "CollisionComponent.h"
#include "SceneSystem.h"

#define DEBUG_COLOR 0.18f, 0.69f, 0.26f

void EscapeRoom::AABBCollisionComponent::UpdatePosition(AABBCollisionComponent* lhs_, AABBCollisionComponent* rhs_)
{
	GameObject* lhs_owner = lhs_->GetOwner();
	GameObject* rhs_owner = rhs_->GetOwner();

	float net_speed = lhs_owner->velocity.GetMag() + rhs_owner->velocity.GetMag() * SceneSystem::GetDeltaTime();
	
	if (lhs_owner->affected_by_collision)
	{
		lhs_owner->velocity = 0.f;
		lhs_owner->position +=
			(lhs_owner->position - rhs_owner->position).GetNormalized() * net_speed;
	}

	if (rhs_owner->affected_by_collision)
	{
		rhs_owner->velocity = 0.f;
		rhs_owner->position += 
			(rhs_owner->position - lhs_owner->position).GetNormalized() * net_speed;
	}
}

EscapeRoom::AABBCollisionComponent::AABBCollisionComponent(GameObject* owner_, Rect& col_zone_) :
IComponent(owner_, GameTypeGUID::GetGUID<AABBCollisionComponent>()),
col_zone(col_zone_),
actual_col_zone(col_zone_)
{
}

bool EscapeRoom::AABBCollisionComponent::Collided(AABBCollisionComponent* other_)
{
	const float this_col_x = actual_col_zone.p4.x;
	const float this_col_y = actual_col_zone.p4.y;
	const float other_col_x = other_->actual_col_zone.p4.x;
	const float other_col_y = other_->actual_col_zone.p4.y;

	const float this_width = actual_col_zone.GetWidth();
	const float this_height = actual_col_zone.GetHeight();
	const float other_width = other_->actual_col_zone.GetWidth();
	const float other_height = other_->actual_col_zone.GetHeight();
	
	if (
		this_col_x < other_col_x + other_width &&
		this_col_x + this_width > other_col_x&&
		this_col_y < other_col_y + other_height &&
		this_col_y + this_height > other_col_y
		)
	{
		// Enter
		if (collided_objects.find(other_) == collided_objects.end())
		{
			collided_objects.emplace(other_);
			
			on_collision_call_backs.EmitAll(other_->GetOwner());
			GameObject* this_owner = owner;
			other_->on_collision_call_backs.EmitAll(std::move(this_owner));
		}
		
		// Stay
		UpdatePosition(this, other_);
		
		return true;
	}
	else
	{
		if (collided_objects.find(other_) != collided_objects.end())
		{
			collided_objects.erase(collided_objects.find(other_));
			
			on_collision_exit_call_backs.EmitAll(other_->GetOwner());
			GameObject* this_owner = owner;
			other_->on_collision_exit_call_backs.EmitAll(std::move(this_owner));
		}
	}
	
	return false;
}

void EscapeRoom::AABBCollisionComponent::UpdateComponent()
{
	actual_col_zone.p1 = owner->transform * col_zone.p1;
	actual_col_zone.p2 = owner->transform * col_zone.p2;
	actual_col_zone.p3 = owner->transform * col_zone.p3;
	actual_col_zone.p4 = owner->transform * col_zone.p4;
}

void EscapeRoom::AABBCollisionComponent::RenderComponent()
{
	LinePack lines = LinePackFactory::MakeRect(col_zone);
	
	GameObject::DrawLine(owner->transform, lines.at(0), DEBUG_COLOR);
	GameObject::DrawLine(owner->transform, lines.at(1), DEBUG_COLOR);
	GameObject::DrawLine(owner->transform, lines.at(2), DEBUG_COLOR);
	GameObject::DrawLine(owner->transform, lines.at(3), DEBUG_COLOR);
}
