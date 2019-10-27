#include "stdafx.h"
#include "CollisionComponent.h"
#include "SceneSystem.h"

#define DEBUG_COLOR 0.18f, 0.69f, 0.26f

void EscapeRoom::ICollisionComponent::UpdateComponent()
{
	// Apply transform
	for (size_t i = 0; i < col_zone.size(); i++)
	{
		actual_col_zone.at(i) = owner->transform * col_zone.at(i);
	}
}

void EscapeRoom::ICollisionComponent::RenderComponent()
{
	if (SceneSystem::GetInstance()->show_debug_info)
	{
		LinePack lines = LinePackFactory::MakePolygon(actual_col_zone);

		for (auto& line : lines)
		{
			App::DrawLine(line.start.x, line.start.y, line.end.x, line.end.y, DEBUG_COLOR);
		}
	}
}

void EscapeRoom::AABBCollisionComponent::UpdatePosition(AABBCollisionComponent* lhs_, AABBCollisionComponent* rhs_)
{
	GameObject* lhs_owner = lhs_->GetOwner();

	const float net_speed =
		lhs_->last_velocity.GetMag() + rhs_->last_velocity.GetMag();

	if (net_speed == 0.f) return;
	
	if (lhs_owner->affected_by_collision)
	{
		const MathVector displace = (lhs_->last_velocity - rhs_->last_velocity).GetNormalized() * -net_speed;
		
		//lhs_owner->velocity = 0.f;
		lhs_owner->velocity = displace;
	}
}

EscapeRoom::AABBCollisionComponent::AABBCollisionComponent(GameObject* owner_, Rect& col_zone_) :
	ICollisionComponent(owner_, col_zone_.GetPoints())
{
}

bool EscapeRoom::AABBCollisionComponent::Collided(ICollisionComponent* other_)
{
	if (dynamic_cast<AABBCollisionComponent*>(other_) == nullptr)
	{
		// Only support AABB collision in this challenge
		// Other component type can be added later if needed
		return false;
	}

	const Rect this_actual_col_zone_rect(actual_col_zone);
	const Rect other_actual_col_zone_rect(other_->GetActualCollisionZone());
	
	const float this_col_x		= this_actual_col_zone_rect.p4.x;
	const float this_col_y		= this_actual_col_zone_rect.p4.y;
	const float other_col_x		= other_actual_col_zone_rect.p4.x;
	const float other_col_y		= other_actual_col_zone_rect.p4.y;

	const float this_width		= this_actual_col_zone_rect.GetWidth();
	const float this_height		= this_actual_col_zone_rect.GetHeight();
	const float other_width		= other_actual_col_zone_rect.GetWidth();
	const float other_height	= other_actual_col_zone_rect.GetHeight();
	
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
			other_->SetLastVelocity(other_->GetOwner()->velocity);
		}
		
		// Stay
		if (!(trigger || other_->GetTrigger()))
		{
			AABBCollisionComponent* other_aabb = dynamic_cast<AABBCollisionComponent*>(other_);
			UpdatePosition(this, other_aabb);
			UpdatePosition(other_aabb, this);
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
			other_->SetLastVelocity(0.f);

			owner->velocity = 0.f;
			other_->GetOwner()->velocity = 0.f;
		}
	}
	
	return false;
}
