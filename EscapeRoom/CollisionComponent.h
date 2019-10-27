#pragma once

#include "IComponent.h"
#include "PathControlComponent.h"

namespace EscapeRoom
{
	struct Rect;

	class ICollisionComponent : public IComponent
	{
	protected:
		Points col_zone;
		Points actual_col_zone;

		bool trigger = false;

		std::set<ICollisionComponent*> collided_objects;

		MathVector last_velocity;
		
	public:
		Signal<void, GameObject*> on_collision_call_backs;
		Signal<void, GameObject*> on_collision_exit_call_backs;
		
		ICollisionComponent(GameObject* owner_, const Points& zone_) :
			IComponent(owner_, GENERATE_COMPONENT_ID(ICollisionComponent)),
			col_zone(zone_),
			actual_col_zone(zone_)
		{
		}

		inline void SetTrigger(const bool value_)
		{
			trigger = value_;
		}

		inline void SetLastVelocity(const MathVector& value_)
		{
			last_velocity = value_;
		}

		inline Points GetActualCollisionZone() const
		{
			return actual_col_zone;
		}

		inline bool GetTrigger() const
		{
			return trigger;
		}

		inline MathVector GetLastVelocity() const
		{
			return last_velocity;
		}
		
		virtual bool Collided(ICollisionComponent* other_) = 0;

		void UpdateComponent() override;

		void RenderComponent() override;
	};

	class AABBCollisionComponent : public ICollisionComponent
	{
	private:
		static void UpdatePosition(AABBCollisionComponent* lhs_, AABBCollisionComponent* rhs_);

		AABBCollisionComponent(GameObject* owner_, Points& col_zone_) :
			ICollisionComponent(owner_, col_zone_)
		{
		}
	public:
		AABBCollisionComponent(GameObject* owner_, Rect& col_zone_);

		bool Collided(ICollisionComponent* other_) override;
	};
}
