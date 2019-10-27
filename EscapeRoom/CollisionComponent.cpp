#include "stdafx.h"
#include "CollisionComponent.h"
#include "SceneSystem.h"

#define DEBUG_COLOR 0.18f, 0.69f, 0.26f

void EscapeRoom::AABBCollisionComponent::UpdatePosition(AABBCollisionComponent* lhs_, AABBCollisionComponent* rhs_)
{
	GameObject* lhs_owner = lhs_->GetOwner();

	const float net_speed =
		lhs_->last_velocity.GetMag() + rhs_->last_velocity.GetMag();

	if (net_speed == 0.f) return;
	
	if (lhs_owner->affected_by_collision)
	{
		MathVector displace = (lhs_->last_velocity - rhs_->last_velocity).GetNormalized() * -net_speed;
		
		//lhs_owner->velocity = 0.f;
		lhs_owner->velocity = displace;
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

			last_velocity = owner->velocity;
			other_->last_velocity = other_->GetOwner()->velocity;
		}
		
		// Stay
		if (!(trigger || other_->trigger))
		{
			UpdatePosition(this, other_);
			UpdatePosition(other_, this);
		}
		
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

			last_velocity = 0.f;
			other_->last_velocity = 0.f;

			owner->velocity = 0.f;
			other_->GetOwner()->velocity = 0.f;
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
