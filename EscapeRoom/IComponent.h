#pragma once

#include "GameObject.h"
#include "GUID.h"

#define GENERATE_COMPONENT_ID(type) GameTypeGUID::GetGUID<type>()

namespace EscapeRoom
{
	class IComponent
	{
	protected:
		GameObject* owner;
		GameTypeGUID::GUIDType type_id;
		
	public:
		explicit IComponent(GameObject* owner_, GameTypeGUID::GUIDType guid_) :
			owner(owner_),
			type_id(guid_)
		{
		}

		GameObject* GetOwner() const
		{
			return owner;
		}

		virtual ~IComponent() = default;
		
		virtual void StartComponent() {};

		virtual void UpdateComponent() {};

		virtual void RenderComponent() {};
	};
}
