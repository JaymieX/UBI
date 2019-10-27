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

		void ServiceAllComponents(std::function<void(IComponent*)>&& service_func_);
		
	public:
		MathVector position;
		MathVector rotation;
		MathVector scale;
		float angle;

		MathMatrix4x4 translate_mat;
		MathMatrix4x4 rotation_mat;
		MathMatrix4x4 scale_mat;
		
		MathMatrix4x4 transform;

		MathVector velocity;
		
		bool affected_by_collision = false;

		std::string tag {"default" };

		explicit GameObject(const std::string& name_, IScene* scene_);
		
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
	if (Util::MapContains(components, GameTypeGUID::GetGUID<Comp>()))
	{
		return
		dynamic_cast<Comp*>(components.at(GameTypeGUID::GetGUID<Comp>()).at(0));
	}

	return nullptr;
}