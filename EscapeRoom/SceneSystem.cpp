#include "stdafx.h"
#include "SceneSystem.h"

#include "IComponent.h"
#include "CollisionComponent.h"

float EscapeRoom::SceneSystem::delta_time = 0.f;

EscapeRoom::GameObject* EscapeRoom::IScene::AddGameObject(std::string&& name_)
{
	if (!Util::MapContains(game_objects, name_))
	{
		game_objects.insert(
			std::make_pair(
				name_,
				std::make_unique<GameObject>(name_, this)
			)
		);

		return game_objects.at(name_).get();
	}

	return nullptr;
}

EscapeRoom::GameObject* EscapeRoom::IScene::GetGameObject(std::string&& name_)
{
	if (Util::MapContains(game_objects, name_))
	{
		return game_objects.at(name_).get();
	}

	return nullptr;
}

void EscapeRoom::IScene::UpdateScene()
{
	quad_tree.Clear();
	for (auto& object : game_objects)
	{
		object.second->UpdateGameObject();
		quad_tree.Insert(object.second.get());
	}

	// Collision
	std::vector<std::unique_ptr<IComponent>>* collision_list =
		&components.at(GameTypeGUID::GetGUID<AABBCollisionComponent>());

	for (size_t i = 0; i < collision_list->size(); i++)
	{
		AABBCollisionComponent* main_obj = dynamic_cast<AABBCollisionComponent*>(collision_list->at(i).get());

		for (size_t j = i + 1; j < collision_list->size(); j++)
		{
			AABBCollisionComponent* other_obj = dynamic_cast<AABBCollisionComponent*>(collision_list->at(j).get());

			main_obj->Collided(other_obj);
		}
	}
}
