#pragma once

#include "GUID.h"

namespace EscapeRoom
{
	class IScene;
	class IComponent;
	
	class GameObject
	{
	private:
		friend class IScene;
		
		std::string name;

		GameObject* parent = nullptr;
		std::set<GameObject*> children;
		
		std::unordered_map<GameTypeGUID::GUIDType, std::vector<IComponent*>> components;

		IScene* owner_scene;

		MathVector position;
		MathVector rotation;
		MathVector scale;
		float angle;

		void ServiceAllComponents(std::function<void(IComponent*)>&& service_func_);

		inline void UpdatePosition()
		{
			translate_mat = MathMatrix::Translate(position);
		}

		inline void UpdateRotation()
		{
			rotation_mat = MathMatrix::Rotate(rotation, angle);
		}

		inline void UpdateScale()
		{
			scale_mat = MathMatrix::Scale(scale);
		}
		
	public:

		MathMatrix4x4 translate_mat;
		MathMatrix4x4 rotation_mat;
		MathMatrix4x4 scale_mat;
		
		MathMatrix4x4 transform;

		MathVector velocity;
		
		bool affected_by_collision = false;

		std::string tag {"default" };

		explicit GameObject(const std::string& name_, IScene* scene_);

		inline void SetPosition(const MathVector& value_)
		{
			position = value_;
			UpdatePosition();
		}

		inline void AppendPosition(const MathVector& value_)
		{
			position += value_;
			UpdatePosition();
		}

		inline void SetRotation(const MathVector& value_)
		{
			rotation = value_;
			UpdateRotation();
		}

		inline void SetAngle(const float value_)
		{
			angle = value_;
			UpdateRotation();
		}

		inline void AppendAngle(const float value_)
		{
			angle += value_;
			UpdateRotation();
		}

		inline void SetScale(const MathVector& value_)
		{
			scale = value_;
			UpdateScale();
		}

		inline void AppendScale(const MathVector& value_)
		{
			scale = value_;
			UpdateScale();
		}

		inline MathVector GetPosition() const
		{
			return position;
		}

		inline MathVector GetRotation() const
		{
			return rotation;
		}

		inline MathVector GetScale() const
		{
			return scale;
		}

		inline float GetAngle() const
		{
			return angle;
		}
		
		void AddChildGameObject(GameObject* game_object_);

		template <typename Comp>
		Comp* GetComponent();
		
		void StartGameObject();

		void UpdateGameObject();

		void RenderGameObject();

		MathMatrix4x4 GetParentHierarchicalTRMatrix();
		MathMatrix4x4 GetParentHierarchicalSMatrix();

		static void DrawLine(MathMatrix4x4& mat_, Line& line_, float r_, float g_, float b_);
	};
}

#include "IComponent.h"
template <typename Comp>
Comp* EscapeRoom::GameObject::GetComponent()
{
	const GameTypeGUID::GUIDType guid = GameTypeGUID::GetGUID<Comp>();
	
	if (Util::MapContains(components, guid))
	{
		return
		dynamic_cast<Comp*>(components.at(guid).at(0));
	}

	return nullptr;
}