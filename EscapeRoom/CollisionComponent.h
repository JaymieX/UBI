#pragma once
#include "IComponent.h"

namespace EscapeRoom
{
	struct Rect;

	class AABBCollisionComponent : public IComponent
	{
	private:
		Rect col_zone;
		Rect actual_col_zone;

		std::set<AABBCollisionComponent*> collided_objects;

		static void UpdatePosition(AABBCollisionComponent* lhs_, AABBCollisionComponent* rhs_);

		MathVector last_velocity;
		
	public:
		Signal<void, GameObject*> on_collision_call_backs;
		Signal<void, GameObject*> on_collision_exit_call_backs;

		bool trigger = false;

		Rect GetActualCollisionZone() const
		{
			return actual_col_zone;
		}
		
		AABBCollisionComponent(GameObject* owner_, Rect& col_zone_);

		bool Collided(AABBCollisionComponent* other_);
		
		void UpdateComponent() override;
		void RenderComponent() override;
	};
}
